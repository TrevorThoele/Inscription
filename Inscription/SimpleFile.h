
#pragma once

#include "Stream.h"

namespace inscription
{
    template<class T>
    class SimpleFile : public Stream<T>
    {
    public:
        using typename Stream<T>::Path;
        using typename Stream<T>::Mode;
        using typename Stream<T>::StreamT;
        using typename Stream<T>::StreamPos;
        using typename Stream<T>::SizeT;
    protected:
        // This constructor will not open the stream automatically
        // Be sure to ChangeMode into something that actually makes sense
        // Call reopen when you're ready to open the stream
        SimpleFile(const Path &path);
        SimpleFile(const Path &path, Mode mode);
    public:
        virtual ~SimpleFile() = 0;
        bool Eof() const;
    };

    template<class T>
    SimpleFile<T>::SimpleFile(const Path &path) : Stream<T>(path)
    {}

    template<class T>
    SimpleFile<T>::SimpleFile(const Path &path, Mode mode) : Stream<T>(path, mode)
    {}

    template<class T>
    SimpleFile<T>::~SimpleFile()
    {}

    template<class T>
    bool SimpleFile<T>::Eof() const
    {
        return this->stream.eof();
    }

    class SimpleInFile : public SimpleFile<std::ifstream>
    {
    public:
        SimpleInFile(const Path &path);

        template<class T>
        SimpleInFile& operator>>(T &var);

        void FillBuffer(char *var, std::streamsize size);
        void SeekG(StreamT::pos_type pos);
    };

    template<class T>
    SimpleInFile& SimpleInFile::operator>>(T &var)
    {
        stream.read(reinterpret_cast<char*>(&var), sizeof(var));
        return *this;
    }

    class SimpleOutFile : public SimpleFile<std::ofstream>
    {
    public:
        SimpleOutFile(const Path &path, bool append = false);

        template<class T>
        SimpleOutFile& operator<<(T &var);

        void SeekP(StreamT::pos_type pos);
    };

    template<class T>
    SimpleOutFile& SimpleOutFile::operator<<(T &var)
    {
        stream.write(reinterpret_cast<const char*>(&var), sizeof(var));
        return *this;
    }
}