#define process_key(d,vk)\
case vk:{\
input.buttons[d].changed = is_down != input.buttons[d].is_down;\
input.buttons[d].is_down = is_down;\
}break;



typedef unsigned int u32;

#define internal static;
#define global static;




inline int clamp(int min, int val, int max)
{
	if (val > max) return max;
	if (val < min) return min;
	return val;
}