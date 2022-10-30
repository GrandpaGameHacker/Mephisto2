#include <string>
#include <unordered_map>
#include <any>
#include <typeinfo>

template <class T>
class IConfigProperty
{
public:
	static_assert(!std::is_pointer_v<T>, "IConfigProperty<T> requires T to be a non pointer type");
	IConfigProperty();
	IConfigProperty(const string& Name);
	IConfigProperty(const string& Name, T& NewValue);
	virtual ~IConfigProperty() {};
	virtual T Get() { return Value };
	virtual void Set(T NewValue) { Value = NewValue };
	virtual void GetString();
protected:
	string PropertyName;
	string PropertyType;
	uint64_t PropertySize = NULL;
	T Value;
};

class IConfig
{
	IConfig() = default;
	virtual ~IConfig() {};
	template<typename T>
	bool AddProperty(string& Name, T Value);
	const IConfigProperty& GetProperty(string& Name)
	std::unordered_map<std::string, IConfigProperty> Options;
};

template<class T>
inline IConfigProperty<T>::IConfigProperty()
{
	PropertyType = typeid(T).Name();
	PropertySize = sizeof(T);
}

template<class T>
inline IConfigProperty<T>::IConfigProperty(const string& Name)
{
	PropertyType = typeid(T).Name();
	PropertyName = Name;
	PropertySize = sizeof(T);
}

template<class T>
inline IConfigProperty<T>::IConfigProperty(const string& Name, T& NewValue)
{
	PropertyType = typeid(T).Name();
	PropertyName = Name;
	PropertySize = sizeof(T);
	Value = NewValue;
}

template<class T>
inline void IConfigProperty<T>::GetString()
{

}
