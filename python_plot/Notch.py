import numpy as np
from scipy import signal

class RealTimeNotchFilter:
    def __init__(self, fs=100.0, freq=50.0, Q=30.0):
        """
        Khởi tạo bộ lọc Notch Real-time.
        
        Tham số:
        - fs (float): Tần số lấy mẫu (Sampling Rate). PHẢI KHỚP với ESP32 (vd: 500Hz).
        - freq (float): Tần số cần cắt (mặc định 50Hz cho điện lưới VN).
        - Q (float): Hệ số phẩm chất (Quality Factor).
            + Q càng cao -> Vết cắt càng hẹp (ít ảnh hưởng tín hiệu tim).
            + Q càng thấp -> Vết cắt càng rộng (cắt nhiễu tốt hơn nhưng dễ làm méo sóng).
            + Q=30 là mức cân bằng tốt cho ECG.
        """
        self.fs = fs
        self.freq = freq
        self.Q = Q
        
        # Tạo hệ số bộ lọc (b, a) cho bộ lọc IIR Notch
        # w0 = freq / (fs/2) -> Tần số chuẩn hóa
        self.b, self.a = signal.iirnotch(freq, Q, fs)
        
        # Khởi tạo trạng thái ban đầu (zi) cho bộ lọc
        # Giúp bộ lọc "nhớ" giá trị cũ để xử lý real-time
        self.zi = signal.lfilter_zi(self.b, self.a)
        
    def process_sample(self, sample_val):
        """
        Lọc từng mẫu đơn lẻ (Sample-by-Sample).
        Input: 1 giá trị float.
        Output: 1 giá trị float đã sạch bóng nhiễu 50Hz.
        """
        # lfilter trả về (kết_quả, trạng_thái_mới)
        filtered_val, self.zi = signal.lfilter(self.b, self.a, [sample_val], zi=self.zi)
        
        return filtered_val[0]

    def reset(self):
        """Reset trạng thái bộ lọc (khi đo lại từ đầu)"""
        self.zi = signal.lfilter_zi(self.b, self.a)