#pragma once
#include "compile_header.h"
#include "patterns.h"
#include "vec.h"
#include <iostream>

namespace KMath
{

// ������
template<std::KReal TReal>
class KMatrix2x2
{
public:
    K_API static const KMatrix2x2 identity;
    K_API static const KMatrix2x2 zero;

    GEN_DEFAULT_CONTRUCTOR_CODE_DEFAULT(KMatrix2x2)

public:
    KMatrix2x2(const KVec2<TReal>& p, const KVec2<TReal>& q) : p(p), q(q) { }

    const KVec2<TReal>& P() const { return p; }
    const KVec2<TReal>& Q() const { return q; }

    const TReal* Matrix() const { return &matrix[0][0]; }
    
    TReal operator[](int32_t subIndex) const { return matrix[subIndex / 10 - 1][subIndex % 10 - 1]; }
    TReal& operator[](int32_t subIndex) { return matrix[subIndex / 10 - 1][subIndex % 10 - 1]; }

    KMatrix2x2 operator*(const KMatrix2x2& rhs) const
    {
        KMatrix2x2 ret;
        ret.m11 = m11 * rhs.m11 + m12 * rhs.m21;
        ret.m12 = m11 * rhs.m12 + m12 * rhs.m22;
        ret.m21 = m21 * rhs.m11 + m22 * rhs.m21;
        ret.m22 = m21 * rhs.m12 + m22 * rhs.m22;
        return ret;
    }
    KMatrix2x2& operator*=(const KMatrix2x2& rhs)
    {
        return *this = *this * rhs;
    }

    template<std::KReal TValue = TReal>
    KMatrix2x2 operator*(TValue value) const { return KMatrix2x2 { p * value, q * value }; }
    template<std::KReal TValue = TReal>
    KMatrix2x2& operator*=(TValue value) { return *this = *this * value; }
    template<std::KReal TValue = TReal>
    KVec2<TValue> operator*(const KVec2<TValue>& rhs) const
    {
        return KVec2<TValue> {
            static_cast<TValue>(rhs.X() * m11 + rhs.Y() * m21),
            static_cast<TValue>(rhs.X() * m12 + rhs.Y() * m22)
        };
    }
    template<std::KReal TValue = TReal>
    KMatrix2x2 operator/(TValue value) const { return operator*(1 / static_cast<TReal>(value)); }
    template<std::KReal TValue = TReal>
    KMatrix2x2& operator/=(TValue value) { return operator*=(1 / static_cast<TReal>(value)); }

    template<std::KReal TValue = TReal>
    KVec2<TValue> TransformVector(const KVec2<TValue>& vec) const
    {
        return *this * vec;
    }

    // ����ת��
    KMatrix2x2 Transpose() const
    {
        return KMatrix2x2 {
            KVec2<TReal> { m11, m21 },
            KVec2<TReal> { m12, m22 }
        };
    }

    // �����2x2���������ʽ
    TReal Det() const { return m11 * m22 - m12 * m21; }
    // �����Ƿ����������
    bool IsSingular() const { return EqualsZero(Det()); } // ����ʽΪ0

    // �������� // ��Ҫȷ�����ﲻ��������� // ����ٶ�һ�������������𣿻���˵һ���ð���������
    // ʩ���������� todo..
    // ������ǰ�������������ʽ
    KMatrix2x2 Inverse() const { return Adjugate() / Det(); }
    // ��������ʽ����
    KMatrix2x2 CofactorMatrix() const
    {
        KMatrix2x2 cof;
        {
            cof.m11 = m22;
            cof.m12 = -m21;
            cof.m21 = -m12;
            cof.m22 = m11;
        }
        return cof;
    }
    // ��������Ǵ�������ʽ�����ת�þ���
    KMatrix2x2 Adjugate() const { return CofactorMatrix().Transpose(); }

protected:
    friend std::ostream& operator<<(std::ostream& out, const KMatrix2x2& rhs)
    {
        out << rhs.p << "\n";
        out << rhs.q << "\n";
        return out;
    }
    
protected:
    union
    {
        struct
        {
            TReal m11, m12;
            TReal m21, m22;
        };

        struct { KVec2<TReal> p, q; };

        TReal matrix[2][2];
    };
};

}