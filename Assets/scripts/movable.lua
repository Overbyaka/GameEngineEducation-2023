input = input_handler:getInputState()

deltaVel = 0.0;
plane_epsilon = 0.1;

if input:test(eIC_GoLeft) then
	deltaVel -= speed
end
if input:test(eIC_GoRight) then
	deltaVel += speed
end

vel_x += deltaVel * delta_time

if input:test(eIC_Jump) then
	if plane_x * pos_x + plane_y * pos_y + plane_z * pos_z < plane_w + plane_epsilon then
		vel_y = jump_speed
	end
end
