#ifndef VECTOR_H
#define VECTOR_H

#define INIT_LENGTH 4

template <class T>
class Vector
{
public:
    //Constructor
    Vector()
    {
        m_size = 0;
        m_length = 4;

        m_array = new T[m_length];
        if (m_array != nullptr)
            m_length = INIT_LENGTH;

    }
    //Destructor
    virtual ~Vector()
    {
        if (m_array != nullptr)
        {
            delete[] m_array;
            m_array = nullptr;
        }
    }
    //Add an element to vector
    void Add(T element)
    {
        if (m_size >= m_length)
            return;
        if (m_size >= m_length / 2)
        {
            m_length *= 2;
            T* temp = new T[m_length];
            if (temp != nullptr)
            {
                for (unsigned i = 0; i < m_size; i++)
                {
                    temp[i] = m_array[i];
                }
                delete[] m_array;
                m_array = temp;
                temp = nullptr;
            }
        }
        m_array[m_size++] = element;
    }
    //Return number of element in vector
    unsigned Size() { return m_size; }
    //Return size of vector
    unsigned GetLength() { return m_length; }
    //Remove an element from last
    void Remove()
    {
        if (m_size > 0)
        {
            m_size--;
        }
    }
    void Clear();
    //Return the element at index
    T At(unsigned index)
    {
        //if(index>=m_size)
        //{
        //    return -1;
        //}
        return m_array[index];
    }
    //override operator
    T& operator[](unsigned i) const
    {
        return m_array[i];
    }



protected:

private:
    T* m_array;             //Vector
    unsigned m_size;        //Size of vector
    unsigned m_length;      //Allocated length of vector

};

#endif // VECTOR_H
