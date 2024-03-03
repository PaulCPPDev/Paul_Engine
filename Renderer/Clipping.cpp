/**
 * @file Clipping.cpp
 * @author Paul Gregor
 * @brief Clips Polygons against Frustum Planes to improve Performance.
 * @version 0.1
 * @date 02.03.2024
 * @copyright University of Bern Applied Sciences
 */

#include "Clipping.h"
#include <SDL2/SDL.h>

#define NUM_PLANES 6
plane_t frustum_planes[NUM_PLANES];

namespace clip {

// Linear interpolation function for floating-point numbers
float float_lerp(float start, float end, float t) {
  return start + t * (end - start);
}

void Clip::init_frustum_planes(float fov_x, float fov_y, float znear, float zfar){
  float cos_half_fov_x = cos(fov_x / 2);
  float sin_half_fov_x = sin(fov_x / 2);
  float cos_half_fov_y = cos(fov_y / 2);
  float sin_half_fov_y = sin(fov_y / 2);

  frustum_planes[LEFT_FRUSTUM_PLANE].point = glm::vec3(0, 0, 0);
  frustum_planes[LEFT_FRUSTUM_PLANE].normal.x = cos_half_fov_x;
  frustum_planes[LEFT_FRUSTUM_PLANE].normal.y = 0;
  frustum_planes[LEFT_FRUSTUM_PLANE].normal.z = sin_half_fov_x;

  frustum_planes[RIGHT_FRUSTUM_PLANE].point = glm::vec3(0, 0, 0);
  frustum_planes[RIGHT_FRUSTUM_PLANE].normal.x = -cos_half_fov_x;
  frustum_planes[RIGHT_FRUSTUM_PLANE].normal.y = 0;
  frustum_planes[RIGHT_FRUSTUM_PLANE].normal.z = sin_half_fov_x;

  frustum_planes[TOP_FRUSTUM_PLANE].point = glm::vec3(0, 0, 0);
  frustum_planes[TOP_FRUSTUM_PLANE].normal.x = 0;
  frustum_planes[TOP_FRUSTUM_PLANE].normal.y = -cos_half_fov_y;
  frustum_planes[TOP_FRUSTUM_PLANE].normal.z = sin_half_fov_y;

  frustum_planes[BOTTOM_FRUSTUM_PLANE].point = glm::vec3(0, 0, 0);
  frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.x = 0;
  frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.y = cos_half_fov_y;
  frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.z = sin_half_fov_y;

  frustum_planes[NEAR_FRUSTUM_PLANE].point = glm::vec3(0, 0, znear);
  frustum_planes[NEAR_FRUSTUM_PLANE].normal.x = 0;
  frustum_planes[NEAR_FRUSTUM_PLANE].normal.y = 0;
  frustum_planes[NEAR_FRUSTUM_PLANE].normal.z = 1;

  frustum_planes[FAR_FRUSTUM_PLANE].point = glm::vec3(0, 0, zfar);
  frustum_planes[FAR_FRUSTUM_PLANE].normal.x = 0;
  frustum_planes[FAR_FRUSTUM_PLANE].normal.y = 0;
  frustum_planes[FAR_FRUSTUM_PLANE].normal.z = -1;
}

polygon_t Clip::polygon_from_triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2){
  polygon_t polygon = {
    .vertices = { v0, v1, v2 },
    .num_vertices = 3
  };
  return polygon;
}

void Clip::triangles_from_polygon(polygon_t* polygon, Triangle triangles[], int* num_triangles){
  for (int i = 0; i < polygon->num_vertices - 2; i++) {
    int index0 = 0;
    int index1 = i + 1;
    int index2 = i + 2;

    triangles[i].vertices[0] = polygon->vertices[index0];
    triangles[i].vertices[1] = polygon->vertices[index1];
    triangles[i].vertices[2] = polygon->vertices[index2];
  }
  *num_triangles = polygon->num_vertices - 2;
}



void Clip::clip_polygon_against_plane(polygon_t* polygon, int plane) {
  glm::vec3 plane_point = frustum_planes[plane].point;
  glm::vec3 plane_normal = frustum_planes[plane].normal;

  // Declare a static array of inside vertices that will be part of the final polygon returned via parameter
  //glm::vec3 inside_vertices[MAX_NUM_POLY_VERTICES];
  std::array<glm::vec3, MAX_NUM_POLY_VERTICES> inside_vertices;
  int num_inside_vertices = 0;

  // Start the current vertex with the first polygon vertex and texture coordinate
  glm::vec3 * current_vertex = &polygon->vertices[0];
   
  // Start the previous vertex with the last polygon vertex and texture coordinate
  glm::vec3* previous_vertex = &polygon->vertices[polygon->num_vertices - 1];
    
  // Calculate the dot product of the current and previous vertex
  float current_dot = 0; 
  float previous_dot = glm::dot( (*previous_vertex- plane_point), plane_normal);

  // Loop all the polygon vertices while the current is different than the last one
  while (current_vertex != &polygon->vertices[polygon->num_vertices]) {
        current_dot = glm::dot((*current_vertex - plane_point), plane_normal);

  // If we changed from inside to outside or from outside to inside
  if (current_dot * previous_dot < 0) {
    // Find the interpolation factor t
    float t = previous_dot / (previous_dot - current_dot);
            
    // Calculate the intersection point I = Q1 + t(Q2-Q1)
    glm::vec3 intersection_point(
      float_lerp(previous_vertex->x, current_vertex->x, t),
      float_lerp(previous_vertex->y, current_vertex->y, t),
      float_lerp(previous_vertex->z, current_vertex->z, t)
      );


      // Insert the intersection point to the list of "inside vertices"
      inside_vertices[num_inside_vertices] = intersection_point;
      num_inside_vertices++;
      }

      // Current vertex is inside the plane
      if (current_dot > 0) {
        // Insert the current vertex to the list of "inside vertices"
        inside_vertices[num_inside_vertices] = *current_vertex;
        num_inside_vertices++;
        }

      // Move to the next vertex
      previous_dot = current_dot;
      previous_vertex = current_vertex;
      current_vertex++;
    }
    
  // At the end, copy the list of inside vertices into the destination polygon (out parameter)
  for (int i = 0; i < num_inside_vertices; i++) {
    polygon->vertices[i] = inside_vertices[i];
  }
  polygon->num_vertices = num_inside_vertices;
}

void Clip::clip_polygon(polygon_t* polygon){
  clip_polygon_against_plane(polygon, LEFT_FRUSTUM_PLANE);
  clip_polygon_against_plane(polygon, RIGHT_FRUSTUM_PLANE);
  clip_polygon_against_plane(polygon, TOP_FRUSTUM_PLANE);
  clip_polygon_against_plane(polygon, BOTTOM_FRUSTUM_PLANE);
  clip_polygon_against_plane(polygon, NEAR_FRUSTUM_PLANE);
  clip_polygon_against_plane(polygon, FAR_FRUSTUM_PLANE);
}

} // namespace clip
