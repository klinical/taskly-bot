//
// Created by zach on 5/19/22.
//

#ifndef DISCORD_BOT_SIMPLEPTR_H
#define DISCORD_BOT_SIMPLEPTR_H

// Homebrew std::unique_ptr<T>

template <typename T>
class SimplePtr {
private:
    T* m_ptr;

public:
    // No copy construction allowed
    SimplePtr(const SimplePtr&) = delete;
    // No copying allowed, shallow or deep
    SimplePtr& operator=(const SimplePtr&) = delete;

    explicit SimplePtr(T* ptr= nullptr): m_ptr{ ptr }
    {};

    // Move constructor, will move ptr.m_ptr to a new this and null out ptr.m_ptr
    // (taking ownership of ptr.m_ptr's memory)
    SimplePtr(SimplePtr&& ptr) noexcept
        : m_ptr{ ptr.m_ptr }
    {
        ptr.m_ptr = nullptr;
    }

    ~SimplePtr()
    {
        delete m_ptr;
    }

    // Move assignment
    // assign to anonymous object/other rvalue (such as return statement) will transfer ownership to *this
    // When assigning another SimplePtr to this, the pointer of the other will be
    // set to a nullptr, and this SimplePtr will now point to the memory previously owned
    // by other
    // const ref as we do not change the SimplePtr object *itself*, it still will still remain being
    // the same object it was before, only modified.
    SimplePtr& operator=(SimplePtr&& ptr) noexcept
    {
        if (&ptr == this)
            return *this;

        // Free what is currently owned
        delete m_ptr;
        // Copy other smart pointer's dump pointer to this object
        m_ptr = ptr.m_ptr;
        // And then set the other internal ptr to null to mark it as moved
        ptr.m_ptr = nullptr;

        return *this;
    }

    // Allow deref operator to do an implicit deref conversion and deref dumb pointer
    T& operator*() const { return *m_ptr; }
    // Accessing pointer members as if accessing dumb pointer directly
    T* operator->() const { return m_ptr; }

    [[nodiscard]]
    bool isNull() const { return m_ptr == nullptr; }
};


#endif //DISCORD_BOT_SIMPLEPTR_H
