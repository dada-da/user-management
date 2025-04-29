# Project Dependencies

Document này mô tả lại các dependencies cũng như cách setup project.

## IDE

Nếu mọi người dùng VS Code thì khi clone project về sẽ có các extension recommend, mọi người nhớ cài là được.
- C/C++
- CMake Tools

Recommend mọi người cài thêm Git Graph để thao tác với git dễ hơn.

Đối với CLion hoặc Visual Studio thì chỉ cần cài dependencies rồi build, chạy project là được.

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

Sau khi hoàn thành phần setup project, mọi người vào đọc [README.md](../config/README.md) trong folder `config` nhé
