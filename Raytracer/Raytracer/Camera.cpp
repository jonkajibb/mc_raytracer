#include "Camera.h"
#include <iostream>
#include <algorithm>
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

const float EPS = 1e-4;

float random_float(float min, float max) {

	return ((float)rand() / RAND_MAX) * (max - min) + min;

};

void Camera::render(Scene s)
{
	//side length of pixels: 0.0025
	//center: y+0.00125, z-0.00125
	float length = 2.0f / H;//0.0025;
	float hLength = length / 2.0f;//0.00125; //half length
	glm::vec3 sphereNormal;
	int depth;
	std::ofstream out("out.ppm");

	out << "P3\n" << H << '\n' << W << '\n' << "255\n";

	glm::vec4 currentP = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

	//Build image plane, 800x800 vertices
	for (int h = 0; h < H; h++)
	{
		for (int w = 0; w < W; w++)
		{
			
			glm::vec4 topLeft  = glm::vec4(0,
				currentP.y-random_float(0.0, hLength),
				currentP.z-random_float(0.0, hLength),
				1.0);
			glm::vec4 topRight = glm::vec4(0,
				currentP.y-random_float(0.0, hLength),
				currentP.z-random_float(hLength, length),
				1.0);
			glm::vec4 botLeft  = glm::vec4(0,
				currentP.y-random_float(hLength, length),
				currentP.z-random_float(0.0, hLength),
				1.0);
			glm::vec4 botRight = glm::vec4(0,
				currentP.y-random_float(hLength, length),
				currentP.z-random_float(hLength, length),
				1.0);
            
			glm::vec3 dir1 = topLeft - eye1;
			glm::vec3 dir2 = topRight - eye1;
			glm::vec3 dir3 = botLeft - eye1;
			glm::vec3 dir4 = botRight - eye1;
            
			Ray ray_topLeft  = Ray(eye1, dir1);
            Ray ray_topRight = Ray(eye1, dir2);
            Ray ray_botLeft  = Ray(eye1, dir3);
            Ray ray_botRight = Ray(eye1, dir4);
			
			//Check if this ray hits a triangle
			//if yes, then call createImage()
			
            depth = 0;
			ColorDbl finalCol1 = castRay(ray_topLeft,  s, depth);
            depth = 0;
            ColorDbl finalCol2 = castRay(ray_topRight, s, depth);
            depth = 0;
            ColorDbl finalCol3 = castRay(ray_botLeft,  s, depth);
            depth = 0;
            ColorDbl finalCol4 = castRay(ray_botRight, s, depth);
            
			ColorDbl finalCol = finalCol1+finalCol2+finalCol3+finalCol4;
			pixelPlane[w][h] = finalCol;

			out << pixelPlane[w][h].color.R
				<< ", " << pixelPlane[w][h].color.G
				<< ", " << pixelPlane[w][h].color.B
				<< std::endl;

			currentP.y = currentP.y - length;

		}
		currentP.z = currentP.z - length; //step down
		currentP.y = 1 - hLength; //start from first position again

		if (h == 800*0.1) std::cout << "10% rendered..." << std::endl;
		if (h == 800*0.2) std::cout << "20% rendered..." << std::endl;
		if (h == 800*0.3) std::cout << "30% rendered..." << std::endl;
		if (h == 800*0.4) std::cout << "40% rendered..." << std::endl;
		if (h == 800*0.5) std::cout << "50% rendered..." << std::endl;
		if (h == 800*0.6) std::cout << "60% rendered..." << std::endl;
		if (h == 800*0.7) std::cout << "70% rendered..." << std::endl;
		if (h == 800*0.8) std::cout << "80% rendered..." << std::endl;
		if (h == 800*0.9) std::cout << "90% rendered..." << std::endl;
		if (h == 800) std::cout << "100% rendered..." << std::endl;
	}
}

ColorDbl Camera::castRay(Ray ray, Scene s, int &depth) {
	float t = 0;
	float d = 1000;
	float minDistance = 10000;
	Triangle minTriangle;
	Sphere minSphere;
	glm::vec3 sphereNormal;
	glm::vec3 lightDir;
	float angle;
	glm::vec3 reflection;
	ColorDbl finalColor;
	ColorDbl indirectLighting = finalColor;
	int maxDepth = 5; //Number of indirect light bounces
	const int N_samples = 1;


	for (unsigned i = 0; i < s.tris.size(); i++)
	{
		if (s.tris[i].rayIntersection(ray, t))
		{
			//A triangle has been intersected, save t (distance between camera and triangle)
			if (t < minDistance) {
				minDistance = t;
				minTriangle = s.tris[i];
                //std::cout << "Minimum distance: " << minDistance << std::endl;
				//ray.endTri = minTriangle;

				//Determine endpoint of ray
				//Before the rays endpoint was changed each time in the intersection func.
				//even though that triangle could be behind something
				ray.end = ray.start + glm::vec4(ray.dir*minDistance, 1.0f);
			}
		}
	}
	//Check if a sphere was also intersected, to set d
	for (int j = 0; j < s.spheres.size(); j++)
	{
		if (s.spheres[j].sphereIntersection(ray, d)) {
			minSphere = s.spheres[j];
			//std::cout << d << std::endl;
			ray.end = glm::vec4(
				ray.start.x + d * ray.dir.x,
				ray.start.y + d * ray.dir.y,
				ray.start.z + d * ray.dir.z,
				1.0f);
			//normal
			sphereNormal = glm::normalize(glm::vec3(ray.end.x - s.spheres[j].center.x,
				ray.end.y - s.spheres[j].center.y,
				ray.end.z - s.spheres[j].center.z));
			


			//MOve ray hit point outside sphere, else the ray is stuck inside
			ray.end.x += sphereNormal.x*EPS;
			ray.end.y += sphereNormal.y*EPS;
			ray.end.z += sphereNormal.z*EPS;

		}
	}

	if (d < t) //If sphere
	{
		if (minSphere.material == Mirror) {
			//Reflection -> find new direction
			reflection = ray.dir - sphereNormal * (2.0f * dot(ray.dir, sphereNormal));
			Ray rRay = Ray(ray.end, reflection);
			return castRay(rRay, s, depth);
		}
		else if (minSphere.material == Diffuse) {
			finalColor = minSphere.color;
			lightDir = s.light.pos - ray.end;
			//std::cout << sphereNormal.X << ", " << sphereNormal.Y << ", " << sphereNormal.Z << std::endl;
			angle = 1 - cos(dot(lightDir, sphereNormal));

			finalColor = minSphere.color * angle;

			//Check if surface should be shadowed
			if (s.shading(ray)) {
				finalColor = finalColor * 0.2;
			}
		}
	}
	else //If triangle
	{
		if (minTriangle.material == Mirror) {
			//Skapa lokalt koordinatsystem

            glm::vec3 myNormal = minTriangle.normal;
            glm::vec3 myIncoming = ray.dir;
            
            //reflection = myIncoming - myNormal*(dot(myNormal, myIncoming))*2;
			reflection = glm::reflect(myIncoming, myNormal);

			Ray rRay = Ray(ray.end, reflection);
			
            finalColor = castRay(rRay, s, depth);
		}
		else if (minTriangle.material == Diffuse) {
			//finalColor = minTriangle.color;
			//lightDir = Direction(s.light.pos.X - ray.end.X, s.light.pos.Y - ray.end.Y, s.light.pos.Z - ray.end.Z);
			lightDir = glm::normalize(s.light.pos - ray.end);

			angle = 1 - cos(dot(minTriangle.normal, lightDir));
            

			if (angle < 0) {
				finalColor = minTriangle.color * 0;
			}
			else {

				finalColor = minTriangle.color * angle;
                
                for(int n = 0; n < N_samples; n++) {
                
                    //----GLOBAL ILLUMINATION----
                    if (depth <= maxDepth) {
                        
                        depth++;
                        //Incoming ray to glm vector
                        //glm::vec3 inc = glm::normalize(glm::vec3(ray.dir.X, ray.dir.Y, ray.dir.Z));
                        float pdf = 1 / (2 * M_PI);

                        //Create local coordinate system------------
						glm::vec3 localZ = minTriangle.normal;
                        glm::vec3 localX = glm::normalize(ray.dir - (localZ * dot(ray.dir, localZ)));
                        glm::vec3 localY = cross(-localX, localZ);
                        //-------------------------------------------

                        //float r1 = (randf() % 100 + 1) / 100; // cos(theta) = N.Light Direction
                        float r1 = random_float(0.0f, 1.0f);
                        //float r2 = (randf() % 100 + 1) / 100;
                        float r2 = random_float(0.0f, 1.0f);

                        float theta = asin(sqrt(r1)); //Inclination angle
                        float phi = 2.0f * M_PI * r2; //Azimuth (TVÄRTOM??)

                        glm::vec3 out = -ray.dir;

                        glm::vec3 outDir = glm::normalize(glm::rotate(out, phi, localZ));
                        outDir = glm::normalize(glm::rotate(outDir, theta, localY));
						//std::cout << outDir.x << ", " << outDir.y << ", " << outDir.z << std::endl;
						glm::vec3 outWorld = glm::vec3(
							outDir.x * localY.x + outDir.y * localZ.x + outDir.z * localX.x,
							outDir.x * localY.y + outDir.y * localZ.y + outDir.z * localX.y,
							outDir.x * localY.z + outDir.y * localZ.z + outDir.z * localX.z);
						
                        /*glm::vec3 outWorld = glm::vec3((ray.end.x + outDir.x),
                                           (ray.end.y + outDir.y),
                                           (ray.end.z + outDir.z));*/
                        
						//IMPLEMENTERA RUSSIAN ROULETTE
                        
                        Ray outRay = Ray(ray.end, outWorld);

                        finalColor = finalColor + (castRay(outRay,s,depth));
                        
                    }
                }
                
                //indirectLighting = indirectLighting / N_samples;
                
				//finalColor = minTriangle.color*angle / M_PI + indirectLighting * 2;
                
				//Check if surface should be shadowed
				if (s.shading(ray)) {
					finalColor = finalColor * 0.5;
				}
			}
		}
	}

	return finalColor;

};
