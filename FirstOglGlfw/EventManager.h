#pragma once

#include "oglforglfw.h"

#include "Ball.h"
#include "Table.h"
#include <vector>

//壁の大きさとか台の大きさを書く変数を追加
const float TABLE_HALF_W = 1.4f;  //台の大きさ
const float TABLE_HALF_D = 2.8f;
const float WALL_T = 0.1f;//壁の厚さ

class EventManager
{
  //C++11以降はここで初期化OK
  bool m_isL = false;
  bool m_isR = false;
  bool m_isM = false;
  EVec2i m_prepos;
  OglForGlfw m_ogl;

  //ここから
  std::vector<Ball> m_balls;//課題3,4で追加、Ballクラスのオブジェクトを入れるvector、複数の球を管理するためにvectorを使う
  Table m_table;//Tableを追加

  bool m_b_drawstroke = false; // 例として3D strokeを描画する
  std::vector<EVec3f> m_stroke;

private: 
  EventManager();

public:
  static EventManager& getInst()
  {
	  static EventManager instance; //staticを使うことで次の呼び出し以降はこのインスタンスが返される→ゲームがいちいち終わらずに、状態を維持できる
	  return instance;//シングルトン→Ballなどは何個もあってもいいけど、EventManagerは一つしかないから、シングルトンにすることで、どこからでも同じEventManagerのインスタンスを呼び出せるようにする
  }
  
  void LBtnDown (EVec2i p, bool ctrl, bool shift);
  void RBtnDown (EVec2i p, bool ctrl, bool shift);
  void MBtnDown (EVec2i p, bool ctrl, bool shift);
  void LBtnUp   (EVec2i p, bool ctrl, bool shift);
  void RBtnUp   (EVec2i p, bool ctrl, bool shift);
  void MBtnUp   (EVec2i p, bool ctrl, bool shift);
  void MouseMove(EVec2i p);
  void MouseWheel(int dx, int dy);
  void KeyDown(int key);
  void KeyUp(int key);
  
  void DrawScene(int screen_width, int height);
};

