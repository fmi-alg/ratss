#ifndef LIB_RATSS_ENUM_H
#define LIB_RATSS_ENUM_H
#pragma once

#include <libratss/constants.h>

namespace LIB_RATSS_NAMESPACE {

typedef enum : int {
	SP_INVALID = 0,
	
	SP_UPPER = 3,
	SP_LOWER = -3,
	
	SP_DIM1_POSITIVE = 1,
	SP_DIM1_NEGATIVE = -1,
	SP_DIM2_POSITIVE = 2,
	SP_DIM2_NEGATIVE = -2,
	SP_DIM3_POSITIVE = 3,
	SP_DIM3_NEGATIVE = -3
	//other values of the form SP_DIMK_POSITIVE = K are valid as well but not listed
	
} PositionOnSphere ;
class SafeSnapType {
public:
#define VA(__NAME, __VALUE) static inline constexpr SafeSnapType __NAME() { return SafeSnapType(values::__VALUE); }
	VA(onSphere, ST_SPHERE)
	VA(onPlane, ST_PLANE)
	VA(paper, ST_PAPER)
	VA(paper2, ST_PAPER)
	
	VA(guaranteeDistance, ST_GUARANTEE_DISTANCE)
	VA(guaranteeSize, ST_GUARANTEE_SIZE)
	
	VA(inputIsExact, ST_INPUT_IS_EXACT)
	
	VA(cf, ST_CF)
	VA(fx, ST_FX)
	VA(fl, ST_FL)
	VA(jp, ST_JP)
	VA(fplll, ST_FPLLL)
	VA(fplllFixedN, ST_FPLLL_FIXED_N)
	VA(bruteFoce, ST_BRUTE_FORCE)
	
	VA(autoSelect, ST_AUTO)
	VA(policyMinSumDenom, ST_AUTO_POLICY_MIN_SUM_DENOM)
	VA(policyMinMaxDenom, ST_AUTO_POLICY_MIN_MAX_DENOM)
	VA(policyMinTotalLimbs, ST_AUTO_POLICY_MIN_TOTAL_LIMBS)
	VA(policyMinSquaredDistance, ST_AUTO_POLICY_MIN_SQUARED_DISTANCE)
	VA(policyMinMaxNorm, ST_AUTO_POLICY_MIN_MAX_NORM)
	
	VA(normalize, ST_NORMALIZE)
#undef VA
public:
	inline constexpr SafeSnapType operator|(SafeSnapType const & other) const { return SafeSnapType(m_v | other.m_v); }
	inline constexpr SafeSnapType operator+(SafeSnapType const & other) const { return SafeSnapType(m_v + other.m_v); }
	inline constexpr SafeSnapType operator&(SafeSnapType const & other) const { return SafeSnapType(m_v | other.m_v); }
	inline constexpr SafeSnapType operator-(SafeSnapType const & other) const { return SafeSnapType(m_v & (~other.m_v)); }
	
	inline constexpr SafeSnapType & operator|=(SafeSnapType const & other) { m_v |= other.m_v; return *this; }
	inline constexpr SafeSnapType & operator+=(SafeSnapType const & other) { m_v += other.m_v; return *this; }
	inline constexpr SafeSnapType & operator&=(SafeSnapType const & other) { m_v &= other.m_v; return *this; }
	inline constexpr SafeSnapType & operator-=(SafeSnapType const & other) { m_v &= ~other.m_v; return *this; }
	
	inline constexpr SafeSnapType operator!=(SafeSnapType const & other) const { return m_v != other.m_v; }
	inline constexpr SafeSnapType operator==(SafeSnapType const & other) const { return m_v == other.m_v; }
public:
	inline constexpr bool empty() const { return m_v == 0; }
	inline constexpr bool is_set(SafeSnapType const & v) const { return (v.m_v & m_v) != 0; }
private:
	enum class values : int {
		ST_NONE=0x0,
		
		ST_SPHERE=0x1, //snap point on sphere
		ST_PLANE=ST_SPHERE*2, //snap point on plane
		ST_PAPER=ST_PLANE*2, //snap point on the plane based on a normalized version of the input point, computed using CORE
		ST_PAPER2=ST_PAPER*2, //snap point on the plane based on a normalized version of the input point, computed using CORE2
		
		ST_SNAP_POSITION_MASK=ST_SPHERE|ST_PLANE|ST_PAPER|ST_PAPER2,
		
		ST_GUARANTEE_DISTANCE=ST_PAPER2*2,
		ST_GUARANTEE_SIZE=ST_GUARANTEE_DISTANCE*2,
		
		ST_GUARANTEE_MASK=ST_GUARANTEE_DISTANCE|ST_GUARANTEE_SIZE,
		
		ST_INPUT_IS_EXACT=ST_GUARANTEE_SIZE*2, //input points are exact
		
		ST_CF=ST_INPUT_IS_EXACT*2,  //snap by continous fraction, compatible with values defined in Calc
		ST_FX=ST_CF*2, //snap by fix point
		ST_FL=ST_FX*2, //snap by floating point
		ST_JP=ST_FL*2,
		///ST_FPLLL variants are all based on the Method described in Lagarias(1985) which uses the
		///LLL algorithm to produce a simultaneous approximation
		ST_FPLLL=ST_JP*2,
		ST_FPLLL_FIXED_N=ST_FPLLL*2, //Compute apx using up to log(N*2^(d/2)) Bits
		ST_BRUTE_FORCE=ST_FPLLL_FIXED_N*2,

		ST_FPLLL_MASK=ST_FPLLL|ST_FPLLL_FIXED_N,
		ST_SNAP_TYPES_MASK=ST_CF|ST_FX|ST_FL|ST_JP|ST_FPLLL_MASK|ST_BRUTE_FORCE,

		//combination types
		ST_CF_GUARANTEE_DISTANCE=ST_CF|ST_GUARANTEE_DISTANCE,
		ST_CF_GUARANTEE_SIZE=ST_CF|ST_GUARANTEE_SIZE,
		ST_JP_GUARANTEE_DISTANCE=ST_JP|ST_GUARANTEE_DISTANCE,
		ST_JP_GUARANTEE_SIZE=ST_JP|ST_GUARANTEE_SIZE,
		ST_FPLLL_GUARANTEE_DISTANCE=ST_FPLLL|ST_GUARANTEE_DISTANCE,
		ST_FPLLL_GUARANTEE_SIZE=ST_FPLLL|ST_GUARANTEE_SIZE, 
		ST_BRUTE_FORCE_DISTANCE=ST_BRUTE_FORCE|ST_GUARANTEE_DISTANCE,
		ST_BRUTE_FORCE_SIZE=ST_BRUTE_FORCE|ST_GUARANTEE_SIZE,

		ST_AUTO=ST_BRUTE_FORCE*2,
		
		ST_AUTO_POLICY_MIN_SUM_DENOM=ST_AUTO*2,
		ST_AUTO_POLICY_MIN_MAX_DENOM=ST_AUTO_POLICY_MIN_SUM_DENOM*2,
		ST_AUTO_POLICY_MIN_TOTAL_LIMBS=ST_AUTO_POLICY_MIN_MAX_DENOM*2,
		ST_AUTO_POLICY_MIN_SQUARED_DISTANCE=ST_AUTO_POLICY_MIN_TOTAL_LIMBS*2,
		ST_AUTO_POLICY_MIN_MAX_NORM=ST_AUTO_POLICY_MIN_SQUARED_DISTANCE*2,
		ST_AUTO_POLICY_MASK=ST_AUTO_POLICY_MIN_SUM_DENOM|ST_AUTO_POLICY_MIN_MAX_DENOM|ST_AUTO_POLICY_MIN_TOTAL_LIMBS|ST_AUTO_POLICY_MIN_SQUARED_DISTANCE|ST_AUTO_POLICY_MIN_MAX_NORM,
		
		ST_NORMALIZE=ST_AUTO_POLICY_MIN_MAX_NORM*2,
		
		//Do not use the values below!
		ST__INTERNAL_NUMBER_OF_SNAPPING_TYPES=7, //this effecivly defines the shift to get from ST_* to ST_AUTO_*
		ST__INTERNAL_AUTO_POLICIES=ST_AUTO_POLICY_MIN_SUM_DENOM|ST_AUTO_POLICY_MIN_MAX_DENOM|ST_AUTO_POLICY_MIN_TOTAL_LIMBS|ST_AUTO_POLICY_MIN_SQUARED_DISTANCE|ST_AUTO_POLICY_MIN_MAX_NORM,
		ST__INTERNAL_AUTO_ALL_WITH_POLICY=ST_SNAP_TYPES_MASK|ST_AUTO|ST__INTERNAL_AUTO_POLICIES
	};
private:
	constexpr SafeSnapType(values v) : m_v(static_cast<int>(v)) {}
	constexpr SafeSnapType(int v) : m_v(v) {}
	constexpr SafeSnapType(SafeSnapType const & other) : m_v(other.m_v) {}
// 	constexpr ~SafeSnapType() {}
private:
	int m_v;
};

typedef enum : int {
	ST_NONE=0x0,
	
	ST_SPHERE=0x1, //snap point on sphere
	ST_PLANE=ST_SPHERE*2, //snap point on plane
	ST_PAPER=ST_PLANE*2, //snap point on the plane based on a normalized version of the input point, computed using CORE
	ST_PAPER2=ST_PAPER*2, //snap point on the plane based on a normalized version of the input point, computed using CORE2
	
	ST_SNAP_POSITION_MASK=ST_SPHERE|ST_PLANE|ST_PAPER|ST_PAPER2,
	
	ST_GUARANTEE_DISTANCE=ST_PAPER2*2,
	ST_GUARANTEE_SIZE=ST_GUARANTEE_DISTANCE*2,
	
	ST_GUARANTEE_MASK=ST_GUARANTEE_DISTANCE|ST_GUARANTEE_SIZE,
	
	ST_INPUT_IS_EXACT=ST_GUARANTEE_SIZE*2, //input points are exact
	
	ST_CF=ST_INPUT_IS_EXACT*2,  //snap by continous fraction, compatible with values defined in Calc
	ST_FX=ST_CF*2, //snap by fix point
	ST_FL=ST_FX*2, //snap by floating point
	ST_JP=ST_FL*2,
	///ST_FPLLL variants are all based on the Method described in Lagarias(1985) which uses the
	///LLL algorithm to produce a simultaneous approximation
	ST_FPLLL=ST_JP*2,
	ST_FPLLL_FIXED_N=ST_FPLLL*2, //Compute apx using up to log(N*2^(d/2)) Bits
	ST_BRUTE_FORCE=ST_FPLLL_FIXED_N*2,

	ST_FPLLL_MASK=ST_FPLLL|ST_FPLLL_FIXED_N,
	ST_SNAP_TYPES_MASK=ST_CF|ST_FX|ST_FL|ST_JP|ST_FPLLL_MASK|ST_BRUTE_FORCE,

	//combination types
	ST_CF_GUARANTEE_DISTANCE=ST_CF|ST_GUARANTEE_DISTANCE,
	ST_CF_GUARANTEE_SIZE=ST_CF|ST_GUARANTEE_SIZE,
	ST_JP_GUARANTEE_DISTANCE=ST_JP|ST_GUARANTEE_DISTANCE,
	ST_JP_GUARANTEE_SIZE=ST_JP|ST_GUARANTEE_SIZE,
	ST_FPLLL_GUARANTEE_DISTANCE=ST_FPLLL|ST_GUARANTEE_DISTANCE,
	ST_FPLLL_GUARANTEE_SIZE=ST_FPLLL|ST_GUARANTEE_SIZE, 
	ST_BRUTE_FORCE_DISTANCE=ST_BRUTE_FORCE|ST_GUARANTEE_DISTANCE,
	ST_BRUTE_FORCE_SIZE=ST_BRUTE_FORCE|ST_GUARANTEE_SIZE,

	ST_AUTO_CF=ST_BRUTE_FORCE*2, //add cf to auto snapping
	ST_AUTO_FX=ST_AUTO_CF*2, //add fx to auto snapping
	ST_AUTO_FL=ST_AUTO_FX*2, //add fl to auto snapping
	ST_AUTO_JP=ST_AUTO_FL*2, //add jp to auto snapping
	ST_AUTO_FPLLL_FIXED_N=ST_AUTO_JP*2, //add fplll to auto snapping
	ST_AUTO_FPLLL=ST_AUTO_FPLLL_FIXED_N*2,
	ST_AUTO_BRUTE_FORCE=ST_AUTO_FPLLL*2,
	ST_AUTO=ST_AUTO_BRUTE_FORCE*2, //select snapping that produces the smallest denominators
	ST_AUTO_ALL=ST_AUTO|ST_AUTO_CF|ST_AUTO_FX|ST_AUTO_JP|ST_AUTO_FPLLL, //try all snappings and use the best one
	ST_AUTO_SNAP_MASK=ST_AUTO_ALL|ST_AUTO_FPLLL_FIXED_N|ST_AUTO_BRUTE_FORCE,
	
	ST_AUTO_POLICY_MIN_SUM_DENOM=ST_AUTO*2,
	ST_AUTO_POLICY_MIN_MAX_DENOM=ST_AUTO_POLICY_MIN_SUM_DENOM*2,
	ST_AUTO_POLICY_MIN_TOTAL_LIMBS=ST_AUTO_POLICY_MIN_MAX_DENOM*2,
	ST_AUTO_POLICY_MIN_SQUARED_DISTANCE=ST_AUTO_POLICY_MIN_TOTAL_LIMBS*2,
	ST_AUTO_POLICY_MIN_MAX_NORM=ST_AUTO_POLICY_MIN_SQUARED_DISTANCE*2,
	ST_AUTO_POLICY_MASK=ST_AUTO_POLICY_MIN_SUM_DENOM|ST_AUTO_POLICY_MIN_MAX_DENOM|ST_AUTO_POLICY_MIN_TOTAL_LIMBS|ST_AUTO_POLICY_MIN_SQUARED_DISTANCE|ST_AUTO_POLICY_MIN_MAX_NORM,
	
	ST_NORMALIZE=ST_AUTO_POLICY_MIN_MAX_NORM*2,
	
	//Do not use the values below!
	ST__INTERNAL_NUMBER_OF_SNAPPING_TYPES=7, //this effecivly defines the shift to get from ST_* to ST_AUTO_*
	ST__INTERNAL_AUTO_POLICIES=ST_AUTO_POLICY_MIN_SUM_DENOM|ST_AUTO_POLICY_MIN_MAX_DENOM|ST_AUTO_POLICY_MIN_TOTAL_LIMBS|ST_AUTO_POLICY_MIN_SQUARED_DISTANCE|ST_AUTO_POLICY_MIN_MAX_NORM,
	ST__INTERNAL_AUTO_ALL_WITH_POLICY=ST_AUTO_ALL|ST__INTERNAL_AUTO_POLICIES
} SnapType;

}//end namespace LIB_RATSS_NAMESPACE

#endif
