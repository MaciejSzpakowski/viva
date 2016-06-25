#pragma once

namespace viva
{
    template<typename T>
    class Array
    {
    private:
        T* arr;
        size_t sz;
    public:
        Array()
        {
            sz = 0;
            arr = nullptr;
        }

        Array(size_t n)
        {
            sz = n;
            arr = new T[n];
        }

        T* data() const
        {
            return arr;
        }

        size_t size() const
        {
            return sz;
        }

        const T& at(size_t index) const
        {
            if (index >= sz)
                throw Error("Array[]", "Argument out of bounds");

            return arr[index];
        }

        T& operator[](size_t index)
        {
            if (index >= sz)
                throw Error("Array[]", "Argument out of bounds");

            return arr[index];
        }

        Array& operator=(Array&& other)
        {
            if (sz != 0)
                delete[] arr;

            sz = other.sz;
            arr = new T[sz];

            return *this;
        }

        Array& operator=(const Array& other)
        {
            if (other != *this)
            {
                if (sz != 0)
                    delete[] arr;

                sz = other.sz;
                arr = new T[sz];

                for (int i = 0; i < sz; i++)
                    arr[i] = other.arr[i];
            }

            return *this;
        }

        void swap(Array& other)
        {
            T* temp = arr;
            arr = other.arr;
            other.arr = temp;
        }

        ~Array()
        {
            if(sz != 0)
                delete[] arr;
        }
    };

	namespace util
	{
        // Read file contents to ASCII string.
        // filepath: path to file
		std::string ReadFileToString(const std::wstring& filepath);

        // Read file to byte vector.
        // dst: destination vector
        void ReadFileToBytes(const std::wstring& filepath, vector<byte>& dst);

        // 
        Size ReadImageToPixels(const std::wstring& filepath, Array<Pixel>& dst);

        Size ReadTgaToPixels(const std::wstring& filepath, Array<Pixel>& dst);
	}
}