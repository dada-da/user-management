# Phân Tích Dự Án: Hệ Thống Đăng Nhập, Đăng Ký và Ví Điểm Thưởng

## 1. Mục Tiêu Dự Án

Xây dựng một hệ thống cho phép người dùng đăng ký, đăng nhập và sử dụng ví điểm thưởng để giao dịch điểm. Hệ thống lưu
trữ thông tin người dùng và quản lý các ví điểm cá nhân, đồng thời hỗ trợ các giao dịch chuyển điểm giữa các ví.

---

## 2. Thành Phần Chính

### 2.1. Đăng Ký Người Dùng

- **Thông tin đầu vào:**
    - Tên người dùng (username)
    - Mật khẩu (password)
- **Quy trình xử lý:**
    - Kiểm tra hợp lệ dữ liệu nhập vào
    - Mã hóa mật khẩu trước khi lưu
    - Tạo bản ghi người dùng mới trong CSDL nếu tên người dùng chưa tồn tại
- **Kết quả:**
    - Người dùng mới được thêm vào hệ thống
    - Một ví điểm mặc định được khởi tạo cho người dùng này (tùy chọn)

### 2.2. Đăng Nhập Người Dùng

- **Thông tin đầu vào:**
    - Tên người dùng
    - Mật khẩu
- **Quy trình xử lý:**
    - Kiểm tra tồn tại người dùng trong CSDL
    - So khớp mật khẩu đã mã hóa
- **Kết quả:**
    - Cho phép truy cập nếu xác thực thành công
    - Từ chối truy cập nếu sai thông tin

---

## 3. Cơ Chế Ví Điểm Thưởng

### 3.1. Mô Tả

- Mỗi người dùng có một **ví điểm** riêng.
- Ví lưu trữ số lượng **điểm** có thể sử dụng để quy đổi ra hàng hóa/dịch vụ.

### 3.2. Giao Dịch Giữa Các Ví

- Người dùng có thể chuyển điểm cho nhau.
- Giao dịch chuyển điểm cần:
    - Xác thực danh tính người gửi
    - Kiểm tra số dư ví người gửi
    - Cập nhật số dư cho cả hai ví nếu hợp lệ

### 3.3. Các Quy Tắc Chính

- Không cho phép chuyển điểm nếu số dư không đủ.
- Giao dịch phải được ghi lại để kiểm tra và truy vết (log giao dịch).
