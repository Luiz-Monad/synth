#ifndef PROPERTY_H
#define PROPERTY_H

template<typename T>
class Property
{
public:

    virtual operator const T&() const;

    virtual Property<T>& operator = (const T& value);

};

template<typename C, typename T>
class PropertyInstance : public Property<T>
{
private:
    
    typedef C* thisPtr;
    thisPtr thisObj;

    typedef T (C::*membFuncPtrGet)();
    membFuncPtrGet get;

    typedef void (C::*membFuncPtrSet)(T);
    membFuncPtrSet set;

public:
    PropertyInstance(thisPtr thisObj, membFuncPtrGet get, membFuncPtrSet set)
    {
        this->thisObj = thisObj;
        this->get = get;
        this->set = set;
    }

    Property<T>& operator = (const T& value)
    {
        (thisObj->*set)(value);
        return (*this);
    };  // eo -

    operator const T&() const
    {
        return ((thisObj->*get)());
    };  // eo ()

};

template<typename T>
class ReadOnlyProperty
{
public:

    virtual operator const T&() const;

};

template<typename C, typename T>
class ReadOnlyPropertyInstance : public ReadOnlyProperty<T>
{
private:
    
    typedef C* thisPtr;
    thisPtr thisObj;

    typedef T (C::*membFuncPtr)();
    membFuncPtr get;

public:
    ReadOnlyPropertyInstance(thisPtr thisObj, membFuncPtr get)
    {
        this->thisObj = thisObj;
        this->get = get;
    }

    operator const T&() const
    {
        return ((thisObj->*get)());
    }

    bool IsNull() const
    {
        return this->thisObj == nullptr;
    }

};

template<typename T>
class ReadOnlyPropertyStatic : public ReadOnlyProperty<T>
{
private:

    typedef T (*membFuncPtr)();
    membFuncPtr get;

public:
    ReadOnlyPropertyStatic(membFuncPtr get)
    {
        this->get = get;
    }

    operator const T&() const
    {
        return ((*get)());
    }

    bool IsNull() const
    {
        return this->get == nullptr;
    }

};

class Functor
{
public:

    template<typename C, typename T>
    static ReadOnlyProperty<T>& New(C* thisObj, T (C::*get)())
    {
        return ReadOnlyPropertyInstance<C, T>(thisObj, get);
    }   
    
    template<typename T>
    static ReadOnlyProperty<T>& New(T (*get)())
    {
        return ReadOnlyPropertyStatic<T>(get);
    }   

    template<typename C, typename T>
    static Property<T>& New(C* thisObj, T (C::*get)(), void (C::*set)(T))
    {
        return PropertyInstance<C, T>(thisObj, get, set);
    }   
    
    template<typename C, typename T>
    static bool IsNull(C* thisObj, const ReadOnlyProperty<T>& obj)
    {
        const ReadOnlyPropertyInstance<C, T>& i = dynamic_cast<const ReadOnlyPropertyInstance<C, T>&>(obj);
        return (i.IsNull());
    }   
	    
};

#endif
