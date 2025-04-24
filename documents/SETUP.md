# Project Dependencies

Document này mô tả lại các dependencies cũng như cách setup project.

## MySQL Connector/C++

MySQL được dùng làm database để đáp ứng yêu cầu dùng database lưu trữ dữ liệu người dùng.
Với library **MySQL Connector/C++**, sử dụng mysqlx/xdevapi.

### Cài đặt:

MySQL

- Download: https://dev.mysql.com/downloads/mysql/

MySQL Connector/C++

- Version sử dụng: 9.2.0
- Source: https://downloads.mysql.com/archives/c-cpp/

#### Troubleshooting:

1. Lưu ý chọn đúng hệ điều hành
2. Chọn đúng phiên bản
3. Nhớ lưu lại thông tin đăng nhập Database được tạo lúc setup MySQL
4. Kiểm tra document cài đặt https://dev.mysql.com/doc/connector-cpp/9.2/en/connector-cpp-installation-binary.html

## Setup Database:

Sau khi hoàn thành phần setup project,
mọi người tạo environment variable cho database nhé.
Các thông tin cần mọi người nhớ lưu lại lúc setup MySQL tránh quên mật khẩu mất thời gian lấy lại.

Thông thường project thật sẽ setup config như này, mọi người chịu khó tìm hiểu, làm quen cách này sau đi làm sẽ dễ hơn nhiều.

```
DB_HOST=localhost giá trị default khi chạy MySQL trên máy
DB_PORT=33060 trên MacOS default là 33060, nếu ai dùng window thì kiểm tra lại nhé
DB_USER=root default user khi cài đặt MySQL
DB_PASSWORD=012345678 Mật khẩu của tài khoản dùng cho MySQL, mọi người nhớ lưu lại, tránh quên thì mất thời gian lấy lại mật khẩu mới
DB_NAME=user_management copy phần này vào là được
```