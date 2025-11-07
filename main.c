#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/sendfile.h>
int main(int argc, char *argv[]) {
    // 检查命令行参数，确保有源文件和目标文件路径
    if (argc != 3) {
        printf("用法：%s 源文件 目标文件\n", argv[0]);
        return 1;
    }

    // 打开源文件（只读模式）
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        perror("打开源文件失败");
        return 1;
    }

    // 打开目标文件（只写模式，不存在则创建，权限为0644）
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("打开目标文件失败");
        close(src_fd);
        return 1;
    }

    // 获取源文件的状态信息，用于获取文件长度
    struct stat stat_buf;
    if (fstat(src_fd, &stat_buf) == -1) {
        perror("获取源文件状态失败");
        close(src_fd);
        close(dest_fd);
        return 1;
    }

    // 使用sendfile进行文件拷贝
    off_t offset = 0;
    ssize_t bytes_copied = sendfile(dest_fd, src_fd, &offset, stat_buf.st_size);
    if (bytes_copied == -1) {
        perror("sendfile拷贝失败");
        close(src_fd);
        close(dest_fd);
        return 1;
    }

    printf("成功拷贝 %zd 字节\n", bytes_copied);

    // 关闭文件描述符
    close(src_fd);
    close(dest_fd);

    return 0;
}
