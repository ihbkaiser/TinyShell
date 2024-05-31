# Practice Project 1 : Tiny Shell
## 1. Danh sách thành viên
- Đoàn Duy Tùng 20224906
- Văn Đức Cường 20220021
- Ngô Đức Chung 20224827
- Nguyễn Văn Đăng 20224946
## 2. Phân chia công việc
| Thành viên | Phần công việc | Deadline |
|-----------|----------------|----------|
| Tùng      | Tạo tiến trình con (foreground, background mode) | 14/06/2024 |
| Cường     | Quản lý tiến trình (List, kill, stop, resume)   | 14/06/2024 |
| Chung     | Các lệnh đặc biệt (date, time, dir,...)         | 14/06/2024 |
| Đăng      | Thực thi file .bat                               | 14/06/2024 |

## 3. Hướng dẫn
- Code phần việc tương ứng thành một file `*.h` trong thư mục `include` (ví dụ `createchildprocess.h`, `killprocess.h`, ...).
- Sau đó code một file `*.cpp` tương ứng để test file `*.h` vừa viết dưới cơ chế dòng lệnh , lưu trong thư mục `test`.
- Mỗi một file `*.h` đó chứa một hàm `void ABC(int argc, TCHAR *argv[])` , có thể có tham số hoặc không (ví dụ tạo tiến trình con cần biết đường dẫn tới file `.exe` cần chạy, hủy bỏ tiến trình cần biết định danh (PID) của nó, ...).
- Nếu cần dùng thêm các hàm khác (như phân tách xâu ký tự, ...), code và lưu trong thư mục `utils`.
- **Tham khảo code tạo tiến trình con của mình** , có thể chạy thử trên cmd:
```
git clone https://github.com/ihbkaiser/TinyShell.git
cd TinyShell
main.exe
Enter command: fork ./test/example.exe
```
## 4. Update 
- 31/5/2024 : Vector processes lưu ở hàm main đã lưu tất cả những tiến trình background đang chạy, có thể sử dụng ngay (nhưng trước khi xử lý cần loại bỏ các tiến trình background chưa kết thúc, bằng cách gọi hàm `bool currentActive()`.
