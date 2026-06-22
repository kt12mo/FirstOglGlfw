#pragma once
class Table
{
private:
	float m_width;//幅
	float m_depth;//奥行き
	float m_height;//高さ

public:
	Table(float width, float depth, float height);//コンストラクタでの定義、private関数にpublicでもらったwidthなどを代入)
	void Draw();//テーブルの描画
	void DrawWall(float w_posX, float w_posY, float w_width, float w_depth);//壁の描画
};