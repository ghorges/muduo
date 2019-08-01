#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <assert.h>
#include <unistd.h>
#include <string>
#include <sys/uio.h>
#include <string.h>
#include <iostream>

class buffer
{
public:
    buffer();

    char* c_str()
    {
        append("\0",1);
        writeindex_--;
        return (char*)&*buffer_.begin() + readindex_;
    }

    int readbytes() const
    {
        assert(writeindex_ >= readindex_);
        return writeindex_ - readindex_;
    }
    int writebytes() const
    {
        return buffer_.size() - writeindex_;
    }
    int prependbytes() const
    {
        return readindex_;
    }
    int append(const char* data,int length)
    {
        makespace(length);
        buffer_.insert(buffer_.begin() + writeindex_,data,data + length);
        writeindex_ += length;
    }
    int set_readindex(int bar){readindex_ = bar;}
    int set_writeindex(int bar){writeindex_ = bar;}

    void makespace(int length)
    {
        if(prependbytes() + writebytes() < length)
        {
            buffer_.resize(buffer_.size() + length);
        }
        else
        {
            int readby = readbytes();
            std::copy(buffer_.begin() + readindex_,
                      buffer_.begin() + writeindex_,
                      buffer_.begin());
            readindex_ = 0;
            writeindex_ = readby;
        }
    }
    int readbuffer(int fd);
private:
    std::vector<char> buffer_;

    int writeindex_;
    int readindex_;
};

#endif // BUFFER_H
