#include "buffer.h"

buffer::buffer() : buffer_(10),readindex_(0),writeindex_(0)
{

}

int buffer::readbuffer(int fd)
{
    char buf[65535];
    bzero(buf,sizeof(buf));
    //ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
    //    struct iovec {
    //                   void  *iov_base;    /* Starting address */
    //                   size_t iov_len;     /* Number of bytes to transfer */
    //               };

    struct iovec iov[2];
    iov[0].iov_base = &*buffer_.begin() + writeindex_;
    iov[0].iov_len = writebytes();
    iov[1].iov_base = buf;
    iov[1].iov_len = sizeof(buf);

    int wrby = writebytes();
    int n = readv(fd,iov,2);
    if(n > 0)
    {
        if(n <= wrby)
        {
            writeindex_ += n;
        }
        else
        {
            writeindex_ += writebytes();
            append(buf,n - wrby);
        }
    }
    return n;
}
