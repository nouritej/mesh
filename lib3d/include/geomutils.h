/* $Id: geomutils.h,v 1.20 2001/11/19 18:16:50 dsanta Exp $ */
#include <3dmodel.h>

#ifndef _GEOMUTILS_PROTO_
#define _GEOMUTILS_PROTO_

#ifdef __cplusplus
extern "C" {
#endif

/* a few useful macros */
#ifndef min
#  define min(__X, __Y) ((__X)<(__Y)?(__X):(__Y))
#endif
#ifndef max
#  define max(__X, __Y) ((__X)>(__Y)?(__X):(__Y))
#endif
#ifndef max3
#  define max3(__X,__Y,__Z) max((__X), max((__Y), (__Z)))
#endif
#ifndef min3
#  define min3(__X,__Y,__Z) min((__X), min((__Y),(__Z)))
#endif

  /* exported functions */
  float dist(vertex_t, vertex_t);
  float cross_product2d(vertex_t, vertex_t, vertex_t);
  float scalprod(vertex_t, vertex_t);
  float norm(vertex_t);
  void normalize(vertex_t*);
  void rotate_3d(vertex_t, vertex_t, double, vertex_t*);
  int inside(vertex_t, vertex_t, float);
  void compute_circle2d(vertex_t, vertex_t, vertex_t, float*, vertex_t*);
  void compute_circle3d(vertex_t, vertex_t, vertex_t, float*, vertex_t*);
  float tri_area(vertex_t, vertex_t, vertex_t);

  /* Inlined faster functions */
  float scalprod_v(const vertex_t*, const vertex_t*);
  float norm2_v(const vertex_t*);
  float norm_v(const vertex_t*);
  float dist_v(const vertex_t*, const vertex_t*);
  float dist2_v(const vertex_t *, const vertex_t *);
  void normalize_v(vertex_t*);
  void substract_v(const vertex_t*, const vertex_t*, vertex_t*);
  void add_v(const vertex_t*, const vertex_t*, vertex_t*);
  void add3_sc_v(float, const vertex_t*, const vertex_t*, const vertex_t*, 
		 vertex_t*);
  void prod_v(float, const vertex_t*, vertex_t*);
  void add_prod_v(float, const vertex_t*, const vertex_t*, vertex_t*);
  void crossprod_v(const vertex_t*, const vertex_t*, vertex_t*);
  void ncrossp_v(const vertex_t*, const vertex_t*, const vertex_t*, vertex_t*);
  float tri_area_v(const vertex_t*, const vertex_t*, const vertex_t*);
  void neg_v(const vertex_t*, vertex_t*);

  /* Version using the dvertex_t (double) type */
  void vertex_d2f_v(const dvertex_t *v1, vertex_t *v2);
  void vertex_f2d_dv(const vertex_t *v1, dvertex_t *v2);
  double scalprod_dv(const dvertex_t*, const dvertex_t*);
  double norm2_dv(const dvertex_t*);
  double norm_dv(const dvertex_t*);
  double dist_dv(const dvertex_t*, const dvertex_t*);
  double dist2_dv(const dvertex_t *, const dvertex_t *);
  void normalize_dv(dvertex_t*);
  void substract_dv(const dvertex_t*, const dvertex_t*, dvertex_t*);
  void add_dv(const dvertex_t*, const dvertex_t*, dvertex_t*);
  void add3_sc_dv(double, const dvertex_t*, const dvertex_t*,
                  const dvertex_t*, dvertex_t*);
  void prod_dv(double, const dvertex_t*, dvertex_t*);
  void add_prod_dv(double, const dvertex_t*, const dvertex_t*,
                   dvertex_t*);
  void crossprod_dv(const dvertex_t*, const dvertex_t*, dvertex_t*);
  void ncrossp_dv(const dvertex_t*, const dvertex_t*,
                  const dvertex_t*, dvertex_t*);
  double tri_area_dv(const dvertex_t*, const dvertex_t*,
                     const dvertex_t*);
  void neg_dv(const dvertex_t*, dvertex_t*);

/* inline definitions */
#ifdef INLINE
# error Name clash with INLINE macro
#endif

#ifdef _GEOMUTILS_C_ /* we are including from the 'master' C file */
# if defined(__GNUC__)
#  define INLINE __inline__
# elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#  define INLINE extern inline
# else
#  define INLINE
# endif
#else /* including from other files */
# if defined (_MSC_VER)
#  define INLINE __inline
# elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 500)
#  define INLINE __inline
# elif defined(__GNUC__)
#  define INLINE extern __inline__
# elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#  define INLINE inline
# endif
#endif

#ifdef INLINE /* give definition of functions */

  /* returns the scalar product of 2 vectors */
  INLINE float scalprod_v(const vertex_t *v1, const vertex_t *v2) {
    return (v1->x*v2->x + v1->y*v2->y + v1->z*v2->z);
  }
  
  /* returns the squared norm of a vector */
  INLINE float norm2_v(const vertex_t *v) {
    return (v->x*v->x + v->y*v->y + v->z*v->z);
  }
  
  /* Returns the norm (i.e. length) of vector v */
  INLINE float norm_v(const vertex_t *v) {
    return (float) sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
  }

  /* Returns the distance between vertices v1 and v2 */
  INLINE float dist_v(const vertex_t *v1, const vertex_t *v2) {
    vertex_t tmp;
  
    tmp.x = v1->x - v2->x;
    tmp.y = v1->y - v2->y;
    tmp.z = v1->z - v2->z;
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)  /* C99 */
    return sqrtf(tmp.x*tmp.x+tmp.y*tmp.y+tmp.z*tmp.z);
#else /* pre-C99 */
    return (float) sqrt(tmp.x*tmp.x+tmp.y*tmp.y+tmp.z*tmp.z);
#endif
  }

  /* Returns the squared distance between vertices v1 and v2 */
  INLINE float dist2_v(const vertex_t *v1, const vertex_t *v2) {
    vertex_t tmp;
  
    tmp.x = v1->x - v2->x;
    tmp.y = v1->y - v2->y;
    tmp.z = v1->z - v2->z;
    
    return tmp.x*tmp.x+tmp.y*tmp.y+tmp.z*tmp.z;
  }
  
  /* Normalizes the vector v to be of unit length */
  INLINE void normalize_v(vertex_t *v) {
    float inv_l;
    inv_l = 1/norm_v(v); /* multiplication is faster than division */
    v->x *= inv_l;
    v->y *= inv_l;
    v->z *= inv_l;
  }
  
  /* Substracts vector v2 from v1 (i.e. v1-v2) and puts the result in vout. It
   * is OK for vout to alias v1 and/or v2. */
  INLINE void substract_v(const vertex_t *v1, const vertex_t *v2,
                          vertex_t *vout) {
  vout->x = v1->x - v2->x;
  vout->y = v1->y - v2->y;
  vout->z = v1->z - v2->z;
  }
  
  /* Adds vectors v1 and v2 and puts the result in vout. It is OK for vout to
   * alias v1 and/or v2. */
  INLINE void add_v(const vertex_t *v1, const vertex_t *v2, vertex_t *vout)
  {
    vout->x = v1->x + v2->x;
    vout->y = v1->y + v2->y;
    vout->z = v1->z + v2->z;
  }

  /* Multiplies vector v by scalar m and puts the result in vout. It is OK for
   * vout to alias v. */
  INLINE void prod_v(float m, const vertex_t *v, vertex_t *vout) {
    vout->x = m*v->x;
    vout->y = m*v->y;
    vout->z = m*v->z;
  }
  

  /* Multiplies v1 by scalar m, adds v2 to it and puts the result in vout */
  INLINE void add_prod_v(float m, const vertex_t *v1, const vertex_t *v2, 
			 vertex_t *vout) {
    vout->x = m*v1->x + v2->x;
    vout->y = m*v1->y + v2->y;
    vout->z = m*v1->z + v2->z;
  }

  INLINE void add3_sc_v(float m, const vertex_t* v0, const vertex_t* v1, 
			const vertex_t* v2, vertex_t* vout) {
    vout->x = m*(v0->x + v1->x + v2->x);
    vout->y = m*(v0->y + v1->y + v2->y);
    vout->z = m*(v0->z + v1->z + v2->z);
  }

  /* Calculates the cross product of vectors v1 and v2 and places the result in
   * vout. It is OK for vout to alias v1 and/or v2. */
  INLINE void crossprod_v(const vertex_t *v1, const vertex_t *v2, 
                          vertex_t *vout) {
    vertex_t res; /* Use temporary to be safe if vout alias v1 and/or v2 */
    res.x = v1->y*v2->z - v1->z*v2->y;
    res.y = v1->z*v2->x - v1->x*v2->z;
    res.z = v1->x*v2->y - v1->y*v2->x;
    *vout = res;
  }
  

  INLINE void ncrossp_v(const vertex_t *v1, const vertex_t *v2,
                        const vertex_t *v3, vertex_t *vout) {
    vertex_t res; /* Use temporary to be safe if vout alias v1 and/or v2 */
    vertex_t u,v;
    float n;
    
    u.x = v2->x - v1->x;
    u.y = v2->y - v1->y;
    u.z = v2->z - v1->z;
    
    v.x = v3->x - v1->x;
    v.y = v3->y - v1->y;
    v.z = v3->z - v1->z;

    /* u^v */
    res.x = u.y*v.z - u.z*v.y;
    res.y = u.z*v.x - u.x*v.z;
    res.z = u.x*v.y - u.y*v.x;

    n = 1/norm_v(&res);
    res.x *= n;
    res.y *= n;
    res.z *= n;

    *vout = res;
  }


  INLINE float tri_area_v(const vertex_t *v1, const vertex_t *v2, 
                          const vertex_t*v3) {
    vertex_t u,v,h;
    float nu2,uv;
    float tmp;
    
    u.x = v1->x - v3->x;
    u.y = v1->y - v3->y;
    u.z = v1->z - v3->z;
    
    v.x = v2->x - v3->x;
    v.y = v2->y - v3->y;
    v.z = v2->z - v3->z;
    
    /* <u,v> */
    uv = u.x*v.x + u.y*v.y +u.z*v.z;

    /* ||u||^2 */
    nu2 = u.x*u.x + u.y*u.y + u.z*u.z;

    tmp = uv/nu2;
    h.x = v.x - u.x*tmp;
    h.y = v.y - u.y*tmp;
    h.z = v.z - u.z*tmp;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)  /* C99 */
    return (norm_v(&h)*sqrtf(nu2)*0.5f);
#else /* pre-C99 */
    return (norm_v(&h)*(float)sqrt(nu2)*0.5f);
#endif
  }

  INLINE void neg_v(const vertex_t *v, vertex_t *vout) {
    vout->x = -v->x;
    vout->y = -v->y;
    vout->z = -v->z;
  }

  /* Versions with doubles */

  /* converts a dvertex_t v1 into a vertex_t v2 */
  INLINE void vertex_d2f_v(const dvertex_t *v1, vertex_t *v2) {
    v2->x = (float) v1->x;
    v2->y = (float) v1->y;
    v2->z = (float) v1->z;
  }

  /* converts a vertex_t v1 into a dvertex_t v2 */
  INLINE void vertex_f2d_dv(const vertex_t *v1, dvertex_t *v2) {
    v2->x = (double) v1->x;
    v2->y = (double) v1->y;
    v2->z = (double) v1->z;
  }

  /* returns the scalar product of 2 vectors */
  INLINE double scalprod_dv(const dvertex_t *v1, const dvertex_t *v2) {
    return (v1->x*v2->x + v1->y*v2->y + v1->z*v2->z);
  }
  
  /* returns the squared norm of a vector */
  INLINE double norm2_dv(const dvertex_t *v) {
    return (v->x*v->x + v->y*v->y + v->z*v->z);
  }
  
  /* Returns the norm (i.e. length) of vector v */
  INLINE double norm_dv(const dvertex_t *v) {
    return (sqrt(v->x*v->x + v->y*v->y + v->z*v->z));
  }

  /* Returns the distance between vertices v1 and v2 */
  INLINE double dist_dv(const dvertex_t *v1, const dvertex_t *v2) {
    dvertex_t tmp;
  
    tmp.x = v1->x - v2->x;
    tmp.y = v1->y - v2->y;
    tmp.z = v1->z - v2->z;
    
    return sqrt(tmp.x*tmp.x+tmp.y*tmp.y+tmp.z*tmp.z);
  }

  /* Returns the squared distance between vertices v1 and v2 */
  INLINE double dist2_dv(const dvertex_t *v1, const dvertex_t *v2) {
    dvertex_t tmp;
  
    tmp.x = v1->x - v2->x;
    tmp.y = v1->y - v2->y;
    tmp.z = v1->z - v2->z;
    
    return tmp.x*tmp.x+tmp.y*tmp.y+tmp.z*tmp.z;
  }
  
  /* Normalizes the vector v to be of unit length */
  INLINE void normalize_dv(dvertex_t *v) {
    double inv_l;
    inv_l = 1/norm_dv(v); /* multiplication is faster than division */
    v->x *= inv_l;
    v->y *= inv_l;
    v->z *= inv_l;
  }
  
  /* Substracts vector v2 from v1 (i.e. v1-v2) and puts the result in vout. It
   * is OK for vout to alias v1 and/or v2. */
  INLINE void substract_dv(const dvertex_t *v1, const dvertex_t *v2,
                           dvertex_t *vout) {
    vout->x = v1->x - v2->x;
    vout->y = v1->y - v2->y;
    vout->z = v1->z - v2->z;
  }
  
  /* Adds vectors v1 and v2 and puts the result in vout. It is OK for vout to
   * alias v1 and/or v2. */
  INLINE void add_dv(const dvertex_t *v1, const dvertex_t *v2,
                     dvertex_t *vout) {
    vout->x = v1->x + v2->x;
    vout->y = v1->y + v2->y;
    vout->z = v1->z + v2->z;
  }

  /* Multiplies vector v by scalar m and puts the result in vout. It is OK for
   * vout to alias v. */
  INLINE void prod_dv(double m, const dvertex_t *v, dvertex_t *vout) {
    vout->x = m*v->x;
    vout->y = m*v->y;
    vout->z = m*v->z;
  }
  

  /* Multiplies v1 by scalar m, adds v2 to it and puts the result in vout */
  INLINE void add_prod_dv(double m, const dvertex_t *v1,
                          const dvertex_t *v2, dvertex_t *vout) {
    vout->x = m*v1->x + v2->x;
    vout->y = m*v1->y + v2->y;
    vout->z = m*v1->z + v2->z;
  }

  INLINE void add3_sc_dv(double m, const dvertex_t* v0, const dvertex_t* v1,
                         const dvertex_t* v2, dvertex_t* vout) {
    vout->x = m*(v0->x + v1->x + v2->x);
    vout->y = m*(v0->y + v1->y + v2->y);
    vout->z = m*(v0->z + v1->z + v2->z);
  }

  /* Calculates the cross product of vectors v1 and v2 and places the result in
   * vout. It is OK for vout to alias v1 and/or v2. */
  INLINE void crossprod_dv(const dvertex_t *v1, const dvertex_t *v2,
                           dvertex_t *vout) {
    dvertex_t res; /* Use temporary to be safe if vout alias v1 and/or v2 */
    res.x = v1->y*v2->z - v1->z*v2->y;
    res.y = v1->z*v2->x - v1->x*v2->z;
    res.z = v1->x*v2->y - v1->y*v2->x;
    *vout = res;
  }
  

  INLINE void ncrossp_dv(const dvertex_t *v1, const dvertex_t *v2,
                         const dvertex_t *v3, dvertex_t *vout) {
    dvertex_t res; /* Use temporary to be safe if vout alias v1 and/or v2 */
    dvertex_t u,v;
    double n;
    
    u.x = v2->x - v1->x;
    u.y = v2->y - v1->y;
    u.z = v2->z - v1->z;
    
    v.x = v3->x - v1->x;
    v.y = v3->y - v1->y;
    v.z = v3->z - v1->z;

    /* u^v */
    res.x = u.y*v.z - u.z*v.y;
    res.y = u.z*v.x - u.x*v.z;
    res.z = u.x*v.y - u.y*v.x;

    n = 1/norm_dv(&res);
    res.x *= n;
    res.y *= n;
    res.z *= n;

    *vout = res;
  }


  INLINE double tri_area_dv(const dvertex_t *v1, const dvertex_t *v2, 
                            const dvertex_t*v3) {
    dvertex_t u,v,h;
    double nu2,uv;
    double tmp;
    
    u.x = v1->x - v3->x;
    u.y = v1->y - v3->y;
    u.z = v1->z - v3->z;
    
    v.x = v2->x - v3->x;
    v.y = v2->y - v3->y;
    v.z = v2->z - v3->z;
    
    /* <u,v> */
    uv = u.x*v.x + u.y*v.y +u.z*v.z;

    /* ||u||^2 */
    nu2 = u.x*u.x + u.y*u.y + u.z*u.z;

    tmp = uv/nu2;
    h.x = v.x - u.x*tmp;
    h.y = v.y - u.y*tmp;
    h.z = v.z - u.z*tmp;



    return (norm_dv(&h)*sqrt(nu2)*0.5);
  }

  INLINE void neg_dv(const dvertex_t *v, dvertex_t *vout) {
    vout->x = -v->x;
    vout->y = -v->y;
    vout->z = -v->z;
  }


#undef INLINE
#endif /* INLINE */
#ifdef __cplusplus
}
#endif

 
#endif
