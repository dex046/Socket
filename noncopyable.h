#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H
class noncopyable
{
//private:
//    noncopyable(noncopyable &);
//    noncopyable(noncopyable &&);
protected:
    noncopyable();
    ~noncopyable();

private:
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;
};

#endif // NONCOPYABLE_H
