#include "Table.h"
#include "oglforglfw.h"
#include "math.h"

Table::Table(float width, float depth, float height) // コンストラクタでの定義、private関数にpublicでもらったwidthなどを代入)
{
    m_width = width; //外寸
    m_depth = depth; //外寸
    m_height = height; 
}


void Table::Draw()//直方体を描画する関数、DrawSceneから呼び出す？ 5/28に消した
{
  // lighting
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  float lightPos[4] = { 10,10,10,1 };//10,10,10,1 ライトの位置
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  // material
  float diff[4] = { 0.8f,0.5f,0.2f,1 };
  float spec[4] = { 1,1,1,1 };
  float amb[4] = { 0.2f,0.2f,0.2f,1 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);

  //貰った変数の半分を計算して、
  float w = m_width / 2.0f; //幅の半分(真ん中から+-に広げる為)
  float d = m_depth / 2.0f; //奥行きの半分
  float z_top = 1.0f; //高さ(表面)ボールが浮かないように1.0
  float z_bottom = z_top - m_height; // 台の裏面の高さも書く
  
  //頂点 8個
  EVec3f p[8] = {
    {-w, -d, z_bottom}, { w, -d, z_bottom}, { w,  d, z_bottom}, {-w,  d, z_bottom}, // 下の面 (Z = -1.0)
    {-w, -d, z_top},    { w, -d, z_top},    { w,  d, z_top},    {-w,  d, z_top}     // 上の面 (Z =  1.0)
  };

  //面 6個 (頂点インデックス 4個ずつ)
  int face[6][4] = { {4,5,6,7}, {1,0,3,2}, {5,1,2,6},
                     {0,4,7,3}, {7,6,2,3}, {0,1,5,4} };
  EVec3f normal[6] = { { 0, 0, 1}, { 0, 0,-1}, { 1, 0, 0},
                       {-1, 0, 0}, { 0, 1, 0}, { 0,-1, 0}};

  glBegin(GL_QUADS);
  for (int f = 0; f < 6; ++f)//こっから
  {
      if (f == 0) // 0番目の面（上面）だったら
      {
          // 表面緑色のマテリアル設定
          float diff_green[4] = { 0.0f, 0.5f, 0.1f, 1 }; // 深い緑
          float spec_green[4] = { 0.1f, 0.1f, 0.1f, 1 }; // ツヤは抑えめ（ラシャっぽい）
          float amb_green[4] = { 0.0f, 0.2f, 0.0f, 1 };
          glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_green);
          glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec_green);
          glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb_green);
          glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 5); // マットな質感
      }
      else // それ以外の面（側面・下面）だったら
      {
          // 側面（例えば木目調のダークブラウン）のマテリアル設定
          float diff_wood[4] = { 0.4f, 0.2f, 0.0f, 1 }; // 濃い茶色
          float spec_wood[4] = { 0.5f, 0.5f, 0.5f, 1 }; // 木のツヤ
          float amb_wood[4] = { 0.1f, 0.1f, 0.1f, 1 };
          glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_wood);
          glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec_wood);
          glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb_wood);
          glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 30); // 少しテカリ
      }

      // 描画処理自体はそのまま
      glNormal3f(normal[f].x(), normal[f].y(), normal[f].z());
      glVertex3fv(p[face[f][0]].data());
      glVertex3fv(p[face[f][1]].data());
      glVertex3fv(p[face[f][2]].data());
      glVertex3fv(p[face[f][3]].data());
  }
  glEnd();
} //ここは、箱の色を変えられる

void Table::DrawWall(float w_posX, float w_posY, float w_width, float w_depth)//壁を描画
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float lightPos[4] = { 10, 10, 10, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


	float w = w_width / 2.0f;//壁の幅の半分
	float d = w_depth / 2.0f;//壁の奥行きの半分
	float z_top = 1.1f;//壁の高さ、テーブルより高くしてボールが当たるようにする(1.0(台の高さ)+0.1
	float z_bottom = 1.0f;//壁の下端はテーブルの上面と同じ高さにする

    EVec3f p[8] = {
      {w_posX - w, w_posY - d, z_bottom}, {w_posX + w, w_posY - d, z_bottom}, {w_posX + w, w_posY + d, z_bottom}, {w_posX - w, w_posY + d, z_bottom},
      {w_posX - w, w_posY - d, z_top},    {w_posX + w, w_posY - d, z_top},    {w_posX + w, w_posY + d, z_top},    {w_posX - w, w_posY + d, z_top}
    };

    int face[6][4] = { {4,5,6,7}, {1,0,3,2}, {5,1,2,6},
                       {0,4,7,3}, {7,6,2,3}, {0,1,5,4} };
    EVec3f normal[6] = { { 0, 0, 1}, { 0, 0,-1}, { 1, 0, 0},
                         {-1, 0, 0}, { 0, 1, 0}, { 0,-1, 0} };

    //壁はすべて濃い焦げ茶色
    float diff_wall[4] = { 0.3f, 0.15f, 0.0f, 1 };
    float spec_wall[4] = { 0.3f, 0.3f,  0.3f, 1 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_wall);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec_wall);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);

    float amb[4] = { 0.1f, 0.1f, 0.1f, 1 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);

    //描画ループ
    glBegin(GL_QUADS);
    for (int f = 0; f < 6; ++f)
    {
        glNormal3f(normal[f].x(), normal[f].y(), normal[f].z());
        glVertex3fv(p[face[f][0]].data());
        glVertex3fv(p[face[f][1]].data());
        glVertex3fv(p[face[f][2]].data());
        glVertex3fv(p[face[f][3]].data());
    }
    glEnd();
}