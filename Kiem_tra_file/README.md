Nội dung bài tập
Mỗi tệp tin và thư mục trên hệ thống file Linux không chỉ chứa dữ liệu mà còn mang theo một lượng lớn "siêu dữ liệu" (metadata) được lưu trong một cấu trúc gọi là inode. Metadata bao gồm:

Loại tệp

Kích thước

Quyền hạn

Thông tin về chủ sở hữu

Các mốc thời gian quan trọng

Các lệnh gọi hệ thống thuộc họ stat() là cách chính xác và hiệu quả nhất để một chương trình C truy cập vào các thông tin này mà không cần phải phân tích kết quả của các lệnh shell như ls -l.

Trong bài tập này, bạn sẽ xây dựng một công cụ dòng lệnh nhỏ có tên filestat, tương tự như lệnh stat có sẵn trên Linux, để đọc và hiển thị các thông tin quan trọng của một tệp bất kỳ.

Bài tập 1: Viết chương trình filestat.c
1.1. Chương trình phải nhận chính xác một tham số từ dòng lệnh, đó là đường dẫn đến một tệp hoặc thư mục.

1.2. Nếu không có tham số nào được cung cấp, hãy in ra hướng dẫn sử dụng (ví dụ: Usage: ./filestat <file_path>) và thoát.

1.3. Sử dụng lệnh gọi hệ thống lstat() để lấy thông tin của đối tượng tại đường dẫn đã cho và lưu vào một biến struct stat.

1.4. Các nội dung cần hiển thị.

File Path: Đường dẫn mà người dùng đã nhập.

File Type: Loại của đối tượng. Bạn phải xác định và in ra được ít nhất 3 loại chính:

"Regular File"

"Directory"

"Symbolic Link"

Gợi ý: Sử dụng các macro S_ISREG(), S_ISDIR(), S_ISLNK() từ <sys/stat.h> để kiểm tra trường st_mode.

Size: Kích thước của tệp, lấy từ trường st_size (in ra kèm đơn vị "bytes").

Last Modified: Thời gian sửa đổi tệp lần cuối.

Lấy giá trị time_t từ trường st_mtime.

Chuyển đổi timestamp này thành một chuỗi ngày-tháng-năm, giờ-phút-giây mà con người có thể đọc được.

Gợi ý: Sử dụng hàm ctime() hoặc strftime() từ <time.h> để định dạng thời gian.