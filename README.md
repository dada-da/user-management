# Hệ thống đăng nhập và đăng ký tài khoản và quản lý ví điểm thưởng

## Giới thiệu dự án

> Dự án Hệ thống đăng nhập và đăng ký chủ yếu liên quan đến quá trình đăng ký người dùng.
Thông tin xác thực người dùng như tên người dùng và mật khẩu được yêu cầu từ người dùng.
Nếu người dùng đăng ký thành công thì với thông tin xác thực được cung cấp, một bản ghi (có thể
là tập tin) của người dùng cụ thể sẽ được tạo trong cơ sở dữ liệu (CSDL).
Ví điểm thưởng là cơ chế quản lý các lượng (đơn vị : điểm) được dùng để quy đổi ra hàng hóa
(còn gọi là hoạt động mua - bán). Giữa các ví có giao dịch chuyển điểm.

## Thành viên

| Tên                | Mã SV      | Công việc được giao                                     |
|--------------------|------------|---------------------------------------------------------|
| Cao Đức Anh        | K24DTCN571 | - Phân tích dự án<br/> - Tạo dự án<br/>- Tạo menu chính |
| Vũ Đinh Minh Thắng | Text       |                                                         |
| Phạm Tuấn Minh     | Text       |                                                         |

## Phân tích dự án

## Getting Started

Xem thêm trong phần [SETUP.md](docs/SETUP.md) với các library và cách setup project

## Project Structure

```
payment-system/
├── src/                      # Source code
├── config/                   # Configuration files
├── docker/                   # Docker-related files
├── db-init/                  # Database initialization
├── examples/                 # Example code
├── CMakeLists.txt            # Build configuration
├── docker-compose.yml        # Docker orchestration
└── README.md                 # Project documentation
```