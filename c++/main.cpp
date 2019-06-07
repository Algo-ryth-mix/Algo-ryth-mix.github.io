#pragma once
#include "math/mathematical_consts.hpp"
#include <cmath>

namespace pixl::math {


	template <class Precision>
	struct angle
	{
		
		angle(const angle&) = default;
		angle(angle&&) = default;

		template <class OP>
		angle<OP> cast() { return angle<OP>(static_cast<OP>(data));}

		angle& operator=(const angle&)=default;
		angle& operator=(angle&&)=default;

		~angle() = default;

		constexpr static angle deg(Precision);
		constexpr static angle rad(Precision);

		constexpr Precision as_deg() const;
		constexpr Precision as_rad() const;

		constexpr static angle asin(Precision);
		constexpr static angle acos(Precision);
		constexpr static angle atan(Precision);
		constexpr static angle atan2(Precision,Precision);

		constexpr Precision sin() const;
		constexpr Precision cos() const;
		constexpr Precision tan() const;

		const Precision data; //in rad

		friend bool operator< (const angle& lhs, const angle& rhs) { return lhs.data < rhs.data; }
		friend bool operator<=(const angle& lhs, const angle& rhs) { return !(rhs < lhs); }
		friend bool operator> (const angle& lhs, const angle& rhs) { return rhs < lhs; }
		friend bool operator>=(const angle& lhs, const angle& rhs) { return !(lhs < rhs); }
		friend bool operator==(const angle& lhs, const angle& rhs) { return lhs.data == rhs.data; }
		friend bool operator!=(const angle& lhs, const angle& rhs) { return !(lhs == rhs); }

		friend angle  operator+ (const angle& lhs,const angle&rhs) { return {lhs.data+rhs.data};}
		friend angle  operator- (const angle& lhs,const angle&rhs) { return {lhs.data-rhs.data};}
		friend angle  operator* (const angle& lhs,const angle&rhs) { return {lhs.data*rhs.data};}
		friend angle  operator/ (const angle& lhs,const angle&rhs) { return {lhs.data/rhs.data};}
		friend angle& operator+=(	   angle& lhs,const angle&rhs) { lhs.data+=rhs.data;return lhs; }
		friend angle& operator-=(	   angle& lhs,const angle&rhs) { lhs.data-=rhs.data;return lhs; }
		friend angle& operator*=(	   angle& lhs,const angle&rhs) { lhs.data*=rhs.data;return lhs; }
		friend angle& operator/=(	   angle& lhs,const angle&rhs) { lhs.data/=rhs.data;return lhs; }
	private:
		angle() = default;
	};

	template <class Precision>
	constexpr angle<Precision> angle<Precision>::deg(Precision val)
	{
		return {deg_to_rad<Precision>()*val};
	}

	template <class Precision>
	constexpr angle<Precision> angle<Precision>::rad(Precision val)
	{
		return {val};
	}

	template <class Precision>
	constexpr Precision angle<Precision>::as_deg() const
	{
		return rad_to_deg<Precision>()*data;
	}

	template <class Precision>
	constexpr Precision angle<Precision>::as_rad() const
	{
		return data;
	}


	template <class Precision>
	constexpr angle<Precision> angle<Precision>::asin(Precision val)
	{
		return {static_cast<Precision>(std::asin(val))};
	}

	template <class Precision>
	constexpr angle<Precision> angle<Precision>::acos(Precision val)
	{
		return {static_cast<Precision>(std::acos(val))};
	}

	template <class Precision>
	constexpr angle<Precision> angle<Precision>::atan(Precision val)
	{
		return {static_cast<Precision>(std::atan(val))};
	}

	template <class Precision>
	constexpr angle<Precision> angle<Precision>::atan2(Precision lhs,Precision rhs)
	{
		return {static_cast<Precision>(std::atan2(lhs,rhs))};
	}

	template <class Precision>
	constexpr Precision angle<Precision>::sin() const
	{
		return std::sin(data);
	}

	template <class Precision>
	constexpr Precision angle<Precision>::cos() const
	{
		return std::cos(data);
	}

	template <class Precision>
	constexpr Precision angle<Precision>::tan() const
	{
		return std::tan(data);
	}
	namespace literals {
		constexpr angle<double> operator""_deg(long double v)
		{
			return angle<double>::deg(v);
		}

		constexpr angle<double> operator""_rad(long double v)
		{
			return angle<double>::rad(v);
		}

		constexpr angle<float> operator""_degf(long double v)
		{
			return angle<float>::deg(static_cast<float>(v));
		}

		constexpr angle<float> operator""_radf(long double v)
		{
			return angle<float>::rad(static_cast<float>(v));
		}

		constexpr angle<unsigned long long int> operator""_deg(unsigned long long int v)
		{
			return angle<unsigned long long int>::deg(v);
		}

		constexpr angle<unsigned long long int> operator""_rad(unsigned long long int v)
		{
			return angle<unsigned long long int>::rad(v);
		}
		constexpr angle<float> operator""_degf(unsigned long long int v)
		{
			return angle<float>::deg(static_cast<float>(v));
		}

		constexpr angle<float> operator""_radf(unsigned long long int v)
		{
			return angle<float>::rad(static_cast<float>(v));
		}

	}
}
