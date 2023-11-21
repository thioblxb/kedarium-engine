#include "Kedarium/Space.hpp"

kdr::Space::Vec3 kdr::Space::normalize(const kdr::Space::Vec3& vector)
{
  float length = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
  return length > 0.f
    ? kdr::Space::Vec3(vector.x / length, vector.y / length, vector.z / length)
    : kdr::Space::Vec3(0.f);
}

kdr::Space::Vec3 kdr::Space::cross(const kdr::Space::Vec3& a, const kdr::Space::Vec3& b)
{
  return kdr::Space::Vec3(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
  );
}

float kdr::Space::dot(const kdr::Space::Vec3& a, const kdr::Space::Vec3& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

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

kdr::Space::Mat4 kdr::Space::lookAt(const kdr::Space::Vec3& eye, const kdr::Space::Vec3& target, const kdr::Space::Vec3& up)
{
  kdr::Space::Vec3 front = kdr::Space::normalize(eye - target);
  kdr::Space::Vec3 right = kdr::Space::normalize(kdr::Space::cross(up, front));
  kdr::Space::Vec3 newUp = kdr::Space::cross(front, right);

  kdr::Space::Mat4 viewMatrix {1.f};
  viewMatrix[0][0] = right.x;
  viewMatrix[1][0] = right.y;
  viewMatrix[2][0] = right.z;
  viewMatrix[0][1] = newUp.x;
  viewMatrix[1][1] = newUp.y;
  viewMatrix[2][1] = newUp.z;
  viewMatrix[0][2] = front.x;
  viewMatrix[1][2] = front.y;
  viewMatrix[2][2] = front.z;
  viewMatrix[3][0] = -kdr::Space::dot(right, eye);
  viewMatrix[3][1] = -kdr::Space::dot(newUp, eye);
  viewMatrix[3][2] = -kdr::Space::dot(front, eye);
  viewMatrix[3][3] = 1.f;
  return viewMatrix;
}
