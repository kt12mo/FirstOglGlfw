#include "EventManager.h"
#include "math.h"


EventManager::EventManager()
    :  m_table(TABLE_HALF_W * 2, TABLE_HALF_D * 2, 2.0f)      //土台
{
    // この3つを課題3.4で追加、半径0.1+ボードの座標1.0=1.1f) EVec3f(x,y,z座),EVec3f((x.y.z速度)),半径
    m_balls = {
        // 白球（下側から打ち出す）
        Ball(EVec3f(0.0f, -2.5f, 1.1f), EVec3f(0.0f, 0.01f, 0.0f), EVec3f(1.0f, 1.0f, 1.0f), 0.1f), // 白球 速度0.01

        // ひし形配置（上側）
        // 1列目（先頭）
        Ball(EVec3f(0.0f,  1.0f,          1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(1.0f, 0.8f, 0.0f), 0.1f), // 1番：黄

        // 2列目
        Ball(EVec3f(-0.1f, 1.0f + 0.173f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(0.0f, 0.0f, 1.0f), 0.1f), // 2番：青
        Ball(EVec3f(0.1f, 1.0f + 0.173f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(1.0f, 0.0f, 0.0f), 0.1f), // 3番：赤

        // 3列目
        Ball(EVec3f(-0.2f, 1.0f + 0.346f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(0.5f, 0.0f, 0.5f), 0.1f), // 4番：紫
        Ball(EVec3f(0.0f, 1.0f + 0.346f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(0.0f, 0.0f, 0.0f), 0.1f), // 8番：黒
        Ball(EVec3f(0.2f, 1.0f + 0.346f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(1.0f, 0.5f, 0.0f), 0.1f), // 5番：オレンジ

        // 4列目
        Ball(EVec3f(-0.3f, 1.0f + 0.519f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(0.0f, 0.5f, 0.0f), 0.1f), // 6番：緑
        Ball(EVec3f(-0.1f, 1.0f + 0.519f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(0.5f, 0.1f, 0.1f), 0.1f), // 7番：栗色
        Ball(EVec3f(0.1f, 1.0f + 0.519f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(1.0f, 0.8f, 0.0f), 0.1f), // 9番：黄
        Ball(EVec3f(0.3f, 1.0f + 0.519f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(0.0f, 0.0f, 1.0f), 0.1f), // 10番：青

        // 5列目
        Ball(EVec3f(-0.4f, 1.0f + 0.692f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(1.0f, 0.0f, 0.0f), 0.1f), // 11番：赤
        Ball(EVec3f(-0.2f, 1.0f + 0.692f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(0.5f, 0.0f, 0.5f), 0.1f), // 12番：紫
        Ball(EVec3f(0.0f, 1.0f + 0.692f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(1.0f, 0.5f, 0.0f), 0.1f), // 13番：オレンジ
        Ball(EVec3f(0.2f, 1.0f + 0.692f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(0.0f, 0.5f, 0.0f), 0.1f), // 14番：緑
        Ball(EVec3f(0.4f, 1.0f + 0.692f, 1.1f), EVec3f(0.0f, 0.0f, 0.0f), EVec3f(0.5f, 0.1f, 0.1f), 0.1f), // 15番：栗色
        };


  m_isL = false;
  m_isR = false;
  m_isM = false;
  
  m_ogl.SetCamera(EVec3f(0,-6,4), EVec3f(0,0,0), EVec3f(0,1,0));//カメラの初期位置,斜めから見えるようにした
  m_ogl.SetClearColor(EVec4f(0.2f, 0.2f, 0.5f, 1.0f));
}

void EventManager::LBtnDown(EVec2i p, bool ctrl, bool shift) 
{
  m_isL = true;
  if (shift) 
  {
    m_stroke.clear();
    EVec3f pos, dir;
    m_ogl.GetCursorRay(p, pos, dir);
    m_stroke.push_back(pos); // camera位置を開始点に入れておく
    m_stroke.push_back(pos+10*dir); //奥行きは適当
    m_b_drawstroke = true;
  }
  
  m_prepos = p;


}

void EventManager::RBtnDown(EVec2i p, bool ctrl, bool shift) 
{
  m_isR = true;
  m_prepos = p;
}

void EventManager::MBtnDown(EVec2i p, bool ctrl, bool shift) 
{
  m_isM = true;
  m_prepos = p;
}

void EventManager::LBtnUp  (EVec2i p, bool ctrl, bool shift) 
{
  m_isL = false;
  m_b_drawstroke = false;
}

void EventManager::RBtnUp  (EVec2i p, bool ctrl, bool shift) 
{
  m_isR = false;
}

void EventManager::MBtnUp  (EVec2i p, bool ctrl, bool shift) 
{
  m_isM = false;
}

void EventManager::MouseMove(EVec2i p) 
{
  if (!m_isL && !m_isR && !m_isM) return;
  int dx = p.x() - m_prepos.x();
  int dy = p.y() - m_prepos.y();

  if (m_b_drawstroke)
  {
    EVec3f pos, dir;
    m_ogl.GetCursorRay(p, pos, dir);
    m_stroke.push_back(pos + 10 * dir);
    std::cout << dir[0] << "," << dir[1] << "," << dir[2] << "\n";
  }
  else 
  {
    if (m_isL)
      m_ogl.RotateCamera(dx, dy);
    else if (m_isR)
      m_ogl.TranslateCamera(dx, dy);
    else if (m_isM)
      m_ogl.ZoomCamera(dy);
  }
  m_prepos = p;
}

void EventManager::MouseWheel(int dx, int dy) {}
void EventManager::KeyDown(int key) {}
void EventManager::KeyUp(int key) {}


 static void DrawFrame() //→座標軸を描画する関数、5/28に消した
{
  glDisable(GL_LIGHTING);
  glLineWidth(2.0f);
  
  glBegin(GL_LINES);
  glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(5, 0, 0);
  glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 5, 0);
  glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 5);
  glEnd();

}

//static void DrawCube()//立方体を描画する関数、DrawSceneから呼び出す？ 5/28に消した
//{
//  // lighting
//  glEnable(GL_DEPTH_TEST);
//  glEnable(GL_LIGHTING);
//  glEnable(GL_LIGHT0);
//
//  float lightPos[4] = { 10,10,10,1 };
//  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//
//  // material
//  float diff[4] = { 0.8f,0.5f,0.2f,1 };
//  float spec[4] = { 1,1,1,1 };
//  float amb[4] = { 0.2f,0.2f,0.2f,1 };
//  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
//  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
//  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
//  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
//  
//  //頂点 8個
//  EVec3f p[8] ={{-1,-1,-1}, { 1,-1,-1}, { 1, 1,-1}, {-1, 1,-1}, 
//                {-1,-1, 1}, { 1,-1, 1}, { 1, 1, 1}, {-1, 1, 1} };
//  //面 6個 (頂点インデックス 4個ずつ)
//  int face[6][4] = { {4,5,6,7}, {1,0,3,2}, {5,1,2,6},
//                     {0,4,7,3}, {7,6,2,3}, {0,1,5,4} };
//  EVec3f normal[6] = { { 0, 0, 1}, { 0, 0,-1}, { 1, 0, 0},
//                       {-1, 0, 0}, { 0, 1, 0}, { 0,-1, 0}};
//
//  glBegin(GL_QUADS);
//  for (int f = 0; f < 6; ++f)
//  {
//    glNormal3f(normal[f].x(), normal[f].y(), normal[f].z());
//    glVertex3fv(p[face[f][0]].data());
//    glVertex3fv(p[face[f][1]].data());
//    glVertex3fv(p[face[f][2]].data());
//    glVertex3fv(p[face[f][3]].data());
//  }
//  glEnd();
//  
//}


EVec3f CalcPos(float theta, float phi)
{
  return EVec3f(
    cos(theta) * cos(phi), 
    sin(phi), 
    -sin(theta) * cos(phi));
}

//void DrawSphere(const EVec3f &pos,float rad, const EVec3f color)
//{
//  // lighting
//  glEnable(GL_DEPTH_TEST);
//  glEnable(GL_LIGHTING);
//  glEnable(GL_LIGHT0);
//
//  float lightPos[4] = { 10,10,10,1 };
//  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//
//  // material   {}
//  float diff[4] = { 0.0f,0.5f,0.8f,1 };
//  float spec[4] = { 1,1,1,1 };
//  float amb[4] = { 0.2f,0.2f,0.2f,1 };
//  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
//  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
//  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
//  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
//
//  const int n = 30;
//  
//  glTranslatef(pos[0], pos[1], pos[2]);
//  glBegin(GL_QUADS);
//  for (int t = 0; t < n; ++t)
//  {
//    for (int p = 0; p < n; ++p)
//    {
//      float t1 =    t    / (n - 1.0f) * M_PI * 2;
//      float t2 = (t + 1) / (n - 1.0f) * M_PI * 2;
//      float p1 =    p    / (n - 1.0f) * M_PI - M_PI / 2;
//      float p2 = (p + 1) / (n - 1.0f) * M_PI - M_PI / 2;
//      
//      EVec3f n0 = CalcPos(t1, p1), x0 = n0 * rad;
//      EVec3f n1 = CalcPos(t2, p1), x1 = n1 * rad;
//      EVec3f n2 = CalcPos(t2, p2), x2 = n2 * rad;
//      EVec3f n3 = CalcPos(t1, p2), x3 = n3 * rad;
//      glNormal3fv(n0.data()); glVertex3fv(x0.data());
//      glNormal3fv(n1.data()); glVertex3fv(x1.data());
//      glNormal3fv(n2.data()); glVertex3fv(x2.data());
//      glNormal3fv(n3.data()); glVertex3fv(x3.data());
//    }
//  }
//  glEnd();
//  glTranslatef( -pos[0], -pos[1], -pos[2]);
//
//}




void EventManager::DrawScene(
    int screen_width,
    int screen_height)
{
    m_ogl.OnDrawBegin(screen_width, screen_height);

   // DrawFrame();

    glColor3f(1, 1, 0);
    glBegin(GL_LINES);
    for (const auto& p : m_stroke) glVertex3fv(p.data());
    glEnd();

    //glDisable(GL_LIGHTING);→三角形を描画するところ消した
    //glBegin(GL_TRIANGLES);
    //glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 0.0f);
    //glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(5.0f, -5.0f, 0.0f);
    //glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 5.0f, 0.0f);
    //glEnd();

    glEnable(GL_LIGHTING);
    //DrawCube();

      //この下から！！ 

	m_table.Draw(); //テーブルを描画する

    m_table.DrawWall(-(TABLE_HALF_W + WALL_T / 2), 0.0f, WALL_T, TABLE_HALF_D * 2 + WALL_T * 2);//右の壁 + WALL_T * 2によって
	m_table.DrawWall((TABLE_HALF_W + WALL_T / 2), 0.0f, WALL_T, TABLE_HALF_D * 2 + WALL_T * 2);//左の壁  壁の四つ角隙間を埋める
	m_table.DrawWall(0.0f, (TABLE_HALF_D + WALL_T / 2), TABLE_HALF_W * 2, WALL_T);//奥の壁
	m_table.DrawWall(0.0f, -(TABLE_HALF_D + WALL_T / 2), TABLE_HALF_W * 2, WALL_T);//手前の壁

    for (int i = 0; i < m_balls.size(); i++)
    {
        m_balls[i].Update();
    }

    //2重for文で、総当たり(衝突)
    for (size_t i = 0; i < m_balls.size(); ++i)
    {
        for (size_t j = i + 1; j < m_balls.size(); ++j)
        {
            Ball::Crash(m_balls[i], m_balls[j]);
        }
    }

    //めり込みが綺麗に治った状態で、最後に一斉に描画
    for (int i = 0; i < m_balls.size(); i++)
    {
        m_balls[i].Draw();   // i番目のボールを描画する
    }
}
