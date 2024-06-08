# Practice Project 1 : Tiny Shell
## 1. Danh sách thành viên
- Đoàn Duy Tùng 20224906
- Văn Đức Cường 20220021
- Ngô Đức Chung 20224827
- Nguyễn Văn Đăng 20224946
## 2. Phân chia công việc
| Thành viên | Phần công việc | Deadline |
|-----------|----------------|----------|
| Tùng      | Tạo tiến trình con (foreground, background mode) | 11/06/2024 |
| Cường     | Quản lý tiến trình (List, kill, stop, resume)   | 11/06/2024 |
| Chung     | Các lệnh đặc biệt (date, time, dir,...)         | 11/06/2024 |
| Đăng      | Thực thi file .bat                               | 11/06/2024 |

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
- 7/6/2024:
  + `List [mode]` tiến trình theo 2 mode: mode `glb` thì list toàn bộ các tiến trình hệ thống (task manager), còn `local` thì chỉ list tiến trình mà shell quản lý (lấy list này ở file `main.cpp`). Mỗi tiến trình nên có PID, status của nó (status: đã end chưa, đang bị tạm dừng, đang chạy, ...).
  + `kill <PID>` : kill tiến trình background với định danh PID, nếu có thì end tiến trình, nếu không tồn tại PID thì báo không tồn tại tiến trình có PID như thế.
  + `stop <PID>` : tương tự như kill, nhưng mà chỉ tạm dừng tiến trình chứ không end.
  + `resume <PID>` : tiếp tục một tiến trình đang tạm dừng.
  + Phần câu lệnh đặc biệt cần có : `date, time, cd, ls` (`cd, ls` thì giống như command prompt của Windows).
  + Thực thi file `.bat` : phải thực thi được file `.bat` đơn giản (1 dòng lệnh) và phức tạp (nhiều dòng lệnh).
  + `path`: list các path được thêm vào shell.
  + `addpath`: add một path vào shell để quản lý.
