# BÁO CÁO THỰC HÀNH TH2: TIMER PHẦN CỨNG, NON-BLOCKING VÀ DEEP SLEEP
- **Họ và tên:** [Điền họ tên bạn]
- **MSSV:** [Điền MSSV bạn]
- **Tài khoản GitHub:** phinamkhanhfm-cloud

---

## 1. Sơ đồ phần cứng
- Sử dụng chung sơ đồ với TH1: LED nối GPIO 2, Nút bấm nối GPIO 4, Biến trở nối GPIO 34[cite: 5, 10].

---

## 2. Tóm tắt kết quả thực hành

### Bài 1: Non-blocking với `millis()`
- **Vấn đề của `delay()`:** Gây tạm dừng CPU, các tác vụ phải chờ nhau làm tổng chu kỳ bị cộng dồn ($500ms + 500ms + 2000ms + 5000ms = 8000ms$), khiến LED và ADC bị trễ nặng[cite: 11].
- **Giải pháp `millis()`:** Sử dụng kỹ thuật đếm thời gian trôi qua (`now - lanTruoc >= interval`). `loop()` chạy liên tục, giúp chớp tắt LED (500ms), đọc ADC (2000ms) và gửi Heartbeat (5000ms) chính xác hoàn toàn độc lập[cite: 12].

### Bài 2: Deep Sleep & Biến nhớ `RTC_DATA_ATTR`
- **RAM thường (`int demThuong`):** Bị xóa hoàn toàn (reset về 1) sau mỗi lần ESP32 thức dậy từ Deep Sleep[cite: 15].
- **Vùng nhớ RTC (`RTC_DATA_ATTR int soLanThuc`):** Giữ nguyên dữ liệu qua các chu kỳ Deep Sleep, biến tích lũy tăng dần (1, 2, 3...)[cite: 15].
- **Cơ chế:** Thức dậy sau 10 giây thông qua timer wakeup (`esp_sleep_enable_timer_wakeup`) và khởi động lại từ đầu hàm `setup()`[cite: 15, 16].

---

## 3. Trả lời câu hỏi ôn tập
1. **Tại sao `delay()` làm sai nhịp?** Vì `delay()` chặn toàn bộ CPU, làm thời gian các tác vụ bị cộng dồn nối tiếp[cite: 11].
2. **Jitter là gì? Tại sao `esp_timer` cho Jitter thấp?** Jitter là độ lệch giữa thời điểm thực thi thực tế và lý tưởng. `esp_timer` hoạt động dạng ngắt phần cứng độc lập nên không bị ảnh hưởng bởi công việc đang chạy trong `loop()`[cite: 13, 14].
3. **Phân biệt Light-sleep và Deep-sleep:**
   * *Light-sleep:* CPU tạm dừng, giữ nguyên RAM thường, tiếp tục chạy ngay tại vị trí dừng.
   * *Deep-sleep:* Dừng hoàn toàn CPU, mất RAM thường (phải dùng `RTC_DATA_ATTR`), khi thức dậy sẽ khởi động lại từ `setup()`[cite: 15, 16].
