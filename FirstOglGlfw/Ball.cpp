#include "Ball.h"
#include "math.h"
#include "EventManager.h"

Ball::Ball(const EVec3f& pos, const EVec3f& vel, EVec3f color, float rad)
{
    m_pos = pos;
    m_vel = vel;
	m_color = color;
    m_rad = rad;
} // コンストラクタでの定義、private関数にpublicでもらったradなどを代入

void Ball::Update()
{
    Move();
    Bounce();
}

void Ball::Move()
{
    m_pos = m_pos + m_vel;
}

void Ball::Bounce()
{
    if (m_pos.x() <= -(TABLE_HALF_W - m_rad)){
        m_pos = EVec3f(-(TABLE_HALF_W - m_rad), m_pos.y(), m_pos.z()); // 壁に当たったときの位置を壁の位置に(速度速くしたらバグるから)
        m_vel[0] = -m_vel[0]; // 速度反転
    }
    else if (m_pos.x() >= (TABLE_HALF_W - m_rad)) {
        m_pos = EVec3f((TABLE_HALF_W - m_rad), m_pos.y(), m_pos.z()); // 壁に当たったときの位置を壁の位置に(速度速くしたらバグるから)
        m_vel[0] = -m_vel[0];
    }
    // ここまでx軸の反射

    if (m_pos.y() <= -(TABLE_HALF_D - m_rad)) {
        m_pos = EVec3f(m_pos.x(), -(TABLE_HALF_D - m_rad), m_pos.z());
        m_vel[1] = -m_vel[1];
    }
    else if (m_pos.y() >= (TABLE_HALF_D - m_rad)) {
        m_pos = EVec3f(m_pos.x(), (TABLE_HALF_D - m_rad), m_pos.z());
        m_vel[1] = -m_vel[1];
    }
    // ここまでy軸の反射
}

void Ball::Crash(Ball& ball1, Ball& ball2)
{
    EVec3f d_pos = ball1.m_pos - ball2.m_pos; // d_posは2つの球の距離のベクトル
    float dSq = d_pos.x() * d_pos.x() + d_pos.y() * d_pos.y(); // 点と点の距離の二乗(x1とx2、y1とy2みたいな)

    float min_d = ball1.m_rad + ball2.m_rad; // 2つの球の半径の和(半径1なら1+1=2)
    float min_dSq = min_d * min_d; // 2つの球の半径の和の二乗

    if (dSq < min_dSq) // 理想の距離(半径の和)よりも本来の距離(点と点の距離)が近いとき
    {
        float d = sqrt(dSq); // dは2つの球の距離
        if (d > 0.0f) {
            EVec3f h_vec = EVec3f(d_pos.x() / d, d_pos.y() / d, 0.0f); // 法線ベクトル

            // 内積を使ってお互いの正面衝突スピードを抜き出す
            float v1 = ball1.m_vel.dot(h_vec); // v1は球1の正面衝突スピード
            float v2 = ball2.m_vel.dot(h_vec); // v2は球2の正面衝突スピード

            // 正面衝突のスピードを入れ替える
            float diff_vec = v1 - v2;
            ball1.m_vel -= h_vec * diff_vec;
            ball2.m_vel += h_vec * diff_vec;

            float gap = min_d - d; // 理想の距離(rad*2)から本来の距離(d)引いた
            ball1.m_pos += h_vec * (gap * 0.5f);//0.5(50％分ワープ)
            ball2.m_pos -= h_vec * (gap * 0.5f);
        }
    } 
}

void Ball::Draw()
{
    glDisable(GL_LIGHTING); // ライティングをOFFにする
    glColor3f(m_color.x(), m_color.y(), m_color.z()); // 色を設定

    for (double j = -M_PI / 2.0; j <= M_PI / 2.0 - 0.2; j += 0.2) { // jは緯度(-π/2 〜 π/2-0.2)、0.2刻みで1段ずつ処理
        double d1 = m_rad * cos(j);       // d1は今の段の円の半径
        double z1 = m_rad * sin(j);       // z1は今の段の円の高さ
        double d2 = m_rad * cos(j + 0.2); // d2は次の段の円の半径
        double z2 = m_rad * sin(j + 0.2); // z2は次の段の円の高さ

        glBegin(GL_QUAD_STRIP); // 四角形の帯を描く関数
        for (double i = 0.0; i <= 2.0 * M_PI; i += 0.1) { // iは経度(0 〜 2π)、円周方向に0.1刻みで頂点を打つ
            double x1 = d1 * cos(i), y1 = d1 * sin(i); // 今の段の頂点のx,y座標 (横成分cos,縦成分sin)
            double x2 = d2 * cos(i), y2 = d2 * sin(i); // 次の段の頂点のx,y座標
            glVertex3d(m_pos.x() + x1, m_pos.y() + y1, m_pos.z() + z1); // 今の段の頂点を打つ(中心座標+ずらす量)
            glVertex3d(m_pos.x() + x2, m_pos.y() + y2, m_pos.z() + z2); // 次の段の頂点を打つ(今の段と交互に→四角形の帯に)
        }
        glEnd();
    }
}




//線で描写する方法
//for (double j = -M_PI / 2.0; j <= M_PI / 2.0; j += 0.2) { // jは描く円の傾き(横方向xy平面の円)(-π/2～π/2)
//    double d = m_rad * cos(j); // dは描く円の半径
//    double z = m_rad * sin(j); // zは描く円の高さ
//
//    glBegin(GL_LINE_LOOP);
//    for (double i = 0.0; i < 2.0 * M_PI; i += 0.1) { // iは描く円の角度
//        double x = d * cos(i); // xは描く円のx座標
//        double y = d * sin(i); // yは描く円のy座標
//
//        glVertex3d(m_pos.x() + x, m_pos.y() + y, m_pos.z() + z); // 描く円の座標は中心座標posにx,y,zを足したもの
//    }
//    glEnd();
//} // 横(xy平面終了)
//
//for (double k = 0.0; k < M_PI; k += 0.01) { // kは描く円の角度(縦方向yz平面の円)
//    glBegin(GL_LINE_LOOP);
//    for (double i = 0.0; i < 2.0 * M_PI; i += 0.1) {
//        double x = m_rad * cos(i) * cos(k); // xは描く円のx座標
//        double y = m_rad * cos(i) * sin(k); // yは描く円のy座標
//        double z = m_rad * sin(i); // zは描く円のz座標
//        glVertex3d(m_pos.x() + x, m_pos.y() + y, m_pos.z() + z); // 描く円の座標は中心座標posにx,y,zを足したもの
//    } // 縦(yz平面終了)
//
//    glEnd();
//}