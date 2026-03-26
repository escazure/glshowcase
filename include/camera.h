#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Camera {
	glm::vec3 position, front, up, right, w_up;	
	float speed, yaw, pitch, fov, height, sensitivity;

	Camera(const glm::vec3 &pos, float _speed, float _sens){
		position = pos;	
		front = glm::vec3(0.0, 0.0, -1.0);
		w_up = glm::vec3(0.0, 1.0, 0.0);

		speed = _speed; 
		sensitivity = _sens;

		yaw = 0.0;
		pitch = 0.0;
		fov = 45.0;

		height = pos.y; 

		update_dir();
	}

	void update_dir(){
		glm::vec3 direction;
		direction.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
		direction.y = std::sin(glm::radians(pitch));
		direction.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
		front = glm::normalize(direction);

		right = glm::normalize(glm::cross(front, w_up));
		up = glm::normalize(glm::cross(right, front));
	}

	void move_forward(float delta){
		position += speed * front * delta;
		position.y = height;
	}
	void move_back(float delta){
		position -= speed * front * delta;
		position.y = height;
	}
	void move_left(float delta){
		position -= speed * right * delta;
		position.y = height;
	}
	void move_right(float delta){
		position += speed * right * delta;
		position.y = height;
	}
	void move_up(float delta){
		position += speed * w_up * delta;
		height = position.y;
	}
	void move_down(float delta){
		position -= speed * w_up * delta;
		height = position.y;
	}

	
	void process_mouse_mov(float xoffset, float yoffset){
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if(pitch > 89.0)
			pitch = 89.0;
		if(pitch < -89.0)
			pitch = -89.0;

		update_dir();
	}

	void process_scroll(float yoffset){
		fov -= yoffset;
		if(fov < 5.0)
			fov = 5.0;
		if(fov > 60.0)
			fov = 60.0;
	}

	glm::mat4 get_view_mat(){
		glm::vec3 zaxis = glm::normalize(position - (position + front));
		glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(w_up), zaxis));
		glm::vec3 yaxis = glm::cross(zaxis, xaxis);

		glm::mat4 pos_mat(1.0);
		pos_mat[3][0] = -position.x;
		pos_mat[3][1] = -position.y;
		pos_mat[3][2] = -position.z;

		glm::mat4 rot_mat(1.0);
		rot_mat[0][0] = xaxis.x;
		rot_mat[1][0] = xaxis.y;
		rot_mat[2][0] = xaxis.z;

		rot_mat[0][1] = yaxis.x;
		rot_mat[1][1] = yaxis.y;
		rot_mat[2][1] = yaxis.z;

		rot_mat[0][2] = zaxis.x;
		rot_mat[1][2] = zaxis.y;
		rot_mat[2][2] = zaxis.z;

		return rot_mat * pos_mat;
	}
};
