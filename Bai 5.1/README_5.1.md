# Cấu hình UART trên STM32F1. Viết chương trình gửi chuỗi ký tự tới máy tính và hiển thị lên terminal 
---
## Mục đích  
Bài thực hành giúp chúng ta làm quen với việc **cấu hình UART (USART)** trên STM32F1 để truyền dữ liệu nối tiếp ra máy tính.  
Thông qua ví dụ, chúng ta sẽ:  

- Hiểu cách cấu hình ngõ ra (Output – TX) và ngõ vào (Input – RX) cho UART.  
- Biết cách khởi tạo ngoại vi USART với tốc độ truyền chuẩn (9600 bps, 8N1).  
- Sử dụng UART để gửi chuỗi dữ liệu ra terminal trên máy tính.  
- Làm quen với phần mềm terminal (Hercules) để kiểm tra kết quả giao tiếp nối tiếp.  

---

## Ý tưởng  
- Sử dụng **USART1** trên STM32F103 với 2 chân: PA9 (TX) và PA10 (RX).  
- Vi điều khiển được cấu hình để định kỳ gửi chuỗi `"Hello from STM32!"` ra cổng UART.  
- Máy tính đóng vai trò là thiết bị nhận, dùng phần mềm **Hercules** để hiển thị dữ liệu nhận được.  
- Chuỗi được gửi lặp lại mỗi giây để dễ quan sát trên terminal.  

---

## Cấu hình  
- Bật clock cho **GPIOA**, **AFIO**, và **USART1**.  
- Thiết lập:  
  - **PA9 (TX)** ở chế độ Alternate Function Push-Pull, tốc độ 50 MHz.  
  - **PA10 (RX)** ở chế độ Input Floating.  
- Cấu hình USART1:  
  - Baudrate: **9600 bps**  
  - Word length: **8 bits**  
  - Stop bit: **1**  
  - Parity: **None**  
  - Mode: **Tx / Rx**  
- Sử dụng **SysTick** để tạo delay.  

---

## Phần cứng kết nối  
- **STM32F103C8T6**.
- **CP2102(UART)**.
- **Kết nối:**  
  - PA9 (TX) → RX module UART  
  - PA10 (RX) → TX module UART  
  - GND STM32 ↔ GND UART  
  
---

**Source code:** [Bài 5.1](RQ1_lib.c)  

**Video Demo:** [Demo 5.1](https://drive.google.com/drive/u/0/folders/1fYEEZR8f3D5NAlzdiDEOioc8Uuw8XTXC)
