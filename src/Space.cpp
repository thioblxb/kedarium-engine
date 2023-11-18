#include "Kedarium/Space.hpp"

kdr::Space::Mat4 kdr::Space::translate(const kdr::Space::Mat4& mat, const kdr::Space::Vec3& vec)
{
  kdr::Space::Mat4 result {mat};
  result[3][0] += vec.x;
  result[3][1] += vec.y;
  result[3][2] += vec.z;
  return result;
}

kdr::Space::Mat4 kdr::Space::perspective(const float fov, const float aspect, const float near, const float far)
{
  kdr::Space::Mat4 result {0.f};
  float tanHalfFov = tanf(fov / 2.f);

  result[0][0] = 1.f / (tanHalfFov * aspect);
  result[1][1] = 1.f / tanHalfFov;
  result[2][2] = (far + near) / (near - far);
  result[2][3] = -1.f;
  result[3][2] = -(2.f * far * near ) / (far - near);

  return result;
}
