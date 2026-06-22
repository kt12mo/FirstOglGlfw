#pragma once //課題3.4の時につくった
#include "oglforglfw.h"

class Ball
{
private://変数(座標、速度、半径、色)
	EVec3f m_pos;
	EVec3f m_vel;
	EVec3f m_color;
	float m_rad;

	void Move();//ボールの移動
	void Bounce();//壁の反射

public:
	Ball(const EVec3f & pos, const EVec3f & vel, EVec3f color, float rad);//privateと、publicで変数名は同じではだめだから
															//radとm_SphereRadなどで分けている
															//EventManager.hで定義している

	void Update();//球の跳ね返りとかの操作
	void Draw();//球の描画

	static void Crash(Ball& ball1, Ball& ball2);//球の衝突
};
