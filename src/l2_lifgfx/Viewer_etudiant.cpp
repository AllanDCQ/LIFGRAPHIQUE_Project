                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                #include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>


#include "draw.h"        // pour dessiner du point de vue d'une camera
#include "Viewer_etudiant.h"

using namespace std;

/*
 * Exemple de definition de fonction permettant la creation du Mesh de votre Objet.
 */
//void ViewerEtudiant::init_votreObjet()
//{
//}


//**************************** Formes de Bases ***************************

void ViewerEtudiant::init_cube()
{
    int i;

    //       4---5
    //      /|  /|
    //     7---6 |
    //     | 0-|-1
    //     |/  |/
    //     3---2

    static float pt[8][3]= { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };
    static int f[6][4]= { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
    static float n[6][3]= { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };

    m_cube = Mesh(GL_TRIANGLE_STRIP);

    for (i=0;i<6;i++)
    {
        m_cube.normal(n[i][0], n[i][1], n[i][2]);

        m_cube.texcoord(0,0);
        m_cube.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

        m_cube.texcoord(1,0);
        m_cube.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

        m_cube.texcoord(0,1);
        m_cube.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

        m_cube.texcoord(1,1);
        m_cube.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );



        m_cube.restart_strip();
    }
}

void ViewerEtudiant::init_disque()
{
    const int div = 25;
    float alpha;
    float step= 2.0 * M_PI / (div);
    m_disque = Mesh( GL_TRIANGLE_FAN );
    m_disque.normal( Vector(0,-1,0) );
    m_disque.vertex( Point(0,0,0)  );
    for(int i=0; i<=div; ++i)
        {
            alpha = i * step;
            m_disque.normal( Vector(0,-1,0) );
            m_disque.vertex( Point(cos(alpha),0, sin(alpha)) );
        }
}

void ViewerEtudiant::init_cylindre()
{
    int i;
    const int div = 25;
    float alpha;
    float step= 2.0 * M_PI / (div);
    m_cylindre = Mesh(GL_TRIANGLE_STRIP);


    for(int i=0; i<=div; ++i)
    {
        alpha = i * step;
        m_cylindre.normal( Vector(cos(alpha),0, sin(alpha)) );
        m_cylindre.texcoord((float)i/div,1);
        m_cylindre.vertex( Point(cos(alpha),-1, sin(alpha)) );
        m_cylindre.normal( Vector(cos(alpha),0, sin(alpha)) );
        m_cylindre.texcoord((float)i/div,0);
        m_cylindre.vertex( Point(cos(alpha), 1, sin(alpha)) );
    }
}

void ViewerEtudiant::init_cone()
{
    const int div = 25;
    float alpha;
    float step= 2.0 * M_PI / (div);

    m_cone= Mesh(GL_TRIANGLE_STRIP);
    for(int i=0;i<=div;++i)
    {
        alpha = i * step;
        m_cone.normal(Vector( cos(alpha)/sqrtf(2.f),1.f/sqrtf(2.f), sin(alpha)/sqrtf(2.f) ));
        m_cone.texcoord((float)i/div,1);
        m_cone.vertex( Point( cos(alpha),0, sin(alpha) ));
        m_cone.normal(Vector( cos(alpha)/sqrtf(2.f),1.f/sqrtf(2.f), sin(alpha)/sqrtf(2.f) ));
        m_cone.texcoord((float)i/div,0);
        m_cone.vertex( Point(0, 1, 0) );

    }
}

void ViewerEtudiant::init_sphere()
{
    const int divBeta= 16;
    const int divAlpha= divBeta/2;
    int i,j;
    float beta, alpha, alpha2;
    m_sphere= Mesh(GL_TRIANGLE_STRIP);
    for(int i=0; i<divAlpha; ++i)
    {
        alpha= -0.5f * M_PI + float(i) * M_PI / divAlpha;
        alpha2= -0.5f * M_PI + float(i+1) * M_PI / divAlpha;
        for(int j=0; j<=divBeta; ++j)
            {
                beta= float(j) * 2.f * M_PI / (divBeta);
                m_sphere.normal( Vector(cos(alpha)*cos(beta),sin(alpha), cos(alpha)*sin(beta)) );
                m_sphere.texcoord(beta/(2.f * M_PI),0.5-alpha/M_PI);
                m_sphere.vertex( Point(cos(alpha)*cos(beta),sin(alpha), cos(alpha)*sin(beta)) );
                m_sphere.normal( Vector(cos(alpha2)*cos(beta), sin(alpha2), cos(alpha2)*sin(beta)) );
                m_sphere.texcoord(beta/(2.f * M_PI),0.5-alpha2/M_PI);
                m_sphere.vertex( Point(cos(alpha2)*cos(beta),sin(alpha2), cos(alpha2)*sin(beta)) );
            }
                m_sphere.restart_strip();
    }


}

void ViewerEtudiant::init_triangle()
{

    m_triangle = Mesh(GL_TRIANGLE_STRIP);

    m_triangle.normal(0,1,0);
    m_triangle.vertex( -2.5,-1.3,-1 );
    m_triangle.vertex( 0,0,0 );
    m_triangle.vertex( 0,0,-2 );
    m_triangle.restart_strip();


    m_triangle.normal(0,0,-1);
    m_triangle.vertex( -2.5,-1.3,-1 );
    m_triangle.vertex( 0,0,-2 );
    m_triangle.vertex( 0,-1,-2 );
    m_triangle.restart_strip();

    m_triangle.normal(0,-1,0);
    m_triangle.vertex( -2.5,-1.3,-1 );
    m_triangle.vertex( 0,-1,-2 );
    m_triangle.vertex( 0,-1,0 );
    m_triangle.restart_strip();

    m_triangle.normal(0,0,1);
    m_triangle.vertex( -2.5,-1.3,-1 );
    m_triangle.vertex( 0,-1,0 );
    m_triangle.vertex( 0,0,0 );
    m_triangle.restart_strip();



}

void ViewerEtudiant::init_drapeau()
{

    m_drapeau = Mesh(GL_TRIANGLE_STRIP);

    int i;

    const int div = 25;
    float alpha;
    float step = M_PI / (div);

    m_drapeau = Mesh(GL_TRIANGLE_STRIP);


    for (int i=0; i<=div; ++i)
    {
        alpha = i * step;
        m_drapeau.normal(Vector(cos(alpha), 0, sin(alpha)));

        m_drapeau.vertex(Point(cos(alpha), -1, sin(alpha)));


        m_drapeau.normal(Vector(cos(alpha), 0, sin(alpha)));

        m_drapeau.vertex(Point(cos(alpha), 1, sin(alpha)));

    }

    m_drapeau.restart_strip();

    for (int i=0; i<=div; ++i)
    {
        alpha = i * step;
        m_drapeau.normal(Vector(-cos(alpha), 0, -sin(alpha)));

        m_drapeau.vertex(Point(cos(alpha), 1, sin(alpha)));


        m_drapeau.normal(Vector(-cos(alpha), 0, -sin(alpha)));

        m_drapeau.vertex(Point(cos(alpha), -1, sin(alpha)));

    }

}



//**************************** Vase ***************************

int ViewerEtudiant::create_vertex_normal_vase(){



    // Nombre de points de la silhouette 2D
    // d?clar? dans la class ViewerEtudiant
    /// Points de la silhouette 2D
    vase_p[0] = Point(0,0,0);
    vase_p[1] = Point(0.6,0.2,0);
    vase_p[2] = Point(1.0,0.4,0);
    vase_p[3] = Point(1.2,0.6,0);
    vase_p[4] = Point(1.3,0.8,0);
    vase_p[5] = Point(1.2, 1.0, 0);
    vase_p[6] = Point(1.0, 1.2,0);
    vase_p[7] = Point(0.8,1.4,0);
    vase_p[8] = Point(1,1.6,0);
    vase_p[9] = Point(1.2,1.8,0) ;

    // Nombre de rotations pour cr?er le vase par rotation
    //vase_NBROT = 20; // d?clar? dans la class ViewerEtudiant

    for(int i=0; i < vase_NBROT; i++){
        //i indice rotation (angle : 2 pi * i / nbrot)
        // Angle qui varie de 0 ? 2 pi
        float teta = 2 * M_PI * i / vase_NBROT;
        // Matrice de rotation de l?angle theta autour axe des y
        // en coordonn?es homog?nes : 4 x 4
        float mat[16] = {
            cos(teta), 0, -sin(teta), 0,
            0, 1, 0, 0,
            sin(teta), 0, cos(teta), 0,
            0, 0, 0, 1 };
        // Calcul des coordonn?es des sommets
        for(int j=0; j < vase_NBPT; j++){
            // j indice du point de la silhouette
            // Application de ma matrice de rotation au point j qui subit la rotation (2 pi * i / nbrot)
            vase_v[i][j].x = mat[0] * vase_p[j].x + mat[1] * vase_p[j].y + mat[2] * vase_p[j].z + mat[3] * 1;
            vase_v[i][j].y = mat[4] * vase_p[j].x + mat[5] * vase_p[j].y + mat[6] * vase_p[j].z + mat[7] * 1;
            vase_v[i][j].z = mat[8] * vase_p[j].x + mat[9] * vase_p[j].y + mat[10] * vase_p[j].z + mat[11] * 1;
        }//for_i
    }//for_i

    // Initialise ? 0 les normales
    for(int i=0; i< vase_NBROT; i++){
        for(int j=0; j< vase_NBPT-1; j++){
            Vector a, b, vntmp;
            a = normalize(vase_v[i][j] - vase_v[i][j+1]);
            b = normalize(vase_v[i][j] - vase_v[(i+1) % vase_NBROT][j]);
            vntmp = cross(a, b); // Produit vectoriel =
            // On r?percute cette normale sur les 4 sommets de la face
            // (accumulation des normales)
            vase_vn[i][j] = vntmp + vase_vn[i][j];
            vase_vn[(i+1) % vase_NBROT][j] = vntmp + vase_vn[(i+1) % vase_NBROT][j];
            vase_vn[(i+1) % vase_NBROT][j+1] = vntmp + vase_vn[(i+1) % vase_NBROT][j+1];
            vase_vn[i][j+1] = vntmp + vase_vn[i][j+1];
        }
    }

    // Normale ? un sommet = moyenne de la normale des 4 sommets de la face
    for(int i=0; i<vase_NBROT; i++){
        for(int j=0; j<vase_NBPT; j++){
            float q = 4.0f;
            if (j == vase_NBPT-1) // Points du bord
            q = 2.0f;
            vase_vn[i][j] = vase_vn[i][j] / q;
        }//for_i
    }//for_j

}

void ViewerEtudiant::init_vase() {



    m_vase = Mesh(GL_TRIANGLES); // Primitive OpenGL
    m_vase.color(1.0, 1.0, 1.0); // Couleur du Mesh
    for(int i=0; i<vase_NBROT; i++){
        for(int j=0; j<vase_NBPT-1; j++){ // Attention boucle de 0 ? vase_NBPT-2 car (j+1)
            // Premier triangle
            m_vase.normal(vase_vn[i][j]);
            m_vase.vertex(vase_v[i][j]);
            m_vase.normal(vase_vn[(i+1) % vase_NBROT][j+1]);
            m_vase.vertex(vase_v[(i+1) % vase_NBROT][j+1]);
            m_vase.normal(vase_vn[(i+1) % vase_NBROT][j]);
            m_vase.vertex(vase_v[(i+1) % vase_NBROT][j]);

            // Second triangle
            m_vase.normal(vase_vn[i][j]);
            m_vase.vertex(vase_v[i][j]);
            m_vase.normal(vase_vn[i][j+1]);
            m_vase.vertex(vase_v[i][j+1]);
            m_vase.normal(vase_vn[(i+1) % vase_NBROT][j+1]);
            m_vase.vertex(vase_v[(i+1) % vase_NBROT][j+1]);
        }//for_j
    }//for_i

}



//**************************** Terrain+Ocean ***************************

Vector ViewerEtudiant::oceanNormal(const Image& im, const int i, const int j){
        // Calcul de la normale au point (i,j) de l?image
        int ip = i-1;
        int in = i+1;
        int jp = j-1;
        int jn = j+1;
        Vector a( ip, im(ip, j).r, j );
        Vector b( in, im(in, j).r, j );
        Vector c( i, im(i, jp).r, jp );
        Vector d( i, im(i, jn).r, jn );
        Vector ab = normalize(b - a);
        Vector cd = normalize(d - c);
        Vector n = cross(cd,ab);
        return n;
    }

Vector ViewerEtudiant::terrainNormal(const Image& im, const int i, const int j){
        // Calcul de la normale au point (i,j) de l?image
        int ip = i-1;
        int in = i+1;
        int jp = j-1;
        int jn = j+1;
        Vector a( ip, im(ip, j).r, j );
        Vector b( in, im(in, j).r, j );
        Vector c( i, im(i, jp).r, jp );
        Vector d( i, im(i, jn).r, jn );
        Vector ab = normalize(b - a);
        Vector cd = normalize(d - c);
        Vector n = cross(cd,ab);
        return n;
    }


void ViewerEtudiant::init_ocean(Mesh& m_ocean, const Image& im) {
    m_ocean = Mesh(GL_TRIANGLE_STRIP);

    for(int i=1;i<im.width()-2;++i){ // Boucle sur les i
        for(int j=1;j<im.height()-1;++j){ // Boucle sur les j
            m_ocean.normal( oceanNormal(im, i+1, j) );
            m_ocean.texcoord(float(i+1)/im.width(),float(j)/im.height());
            m_ocean.vertex( Point(i+1,5.f*im(i+1, j).r, j) );

            m_ocean.normal( oceanNormal(im, i, j) );
            m_ocean.texcoord(float(i+1)/im.width(),float(j)/im.height());
            m_ocean.vertex( Point(i, 5.f*im(i, j).r, j) );
        }
        m_ocean.restart_strip();
    }
}

void ViewerEtudiant::init_terrain(Mesh& m_terrain, const Image& im) {
    m_terrain = Mesh(GL_TRIANGLE_STRIP);

    for(int i=1;i<im.width()-2;++i){ // Boucle sur les i
        for(int j=1;j<im.height()-1;++j){ // Boucle sur les j
            m_terrain.normal( terrainNormal(im, i+1, j) );
            m_terrain.texcoord(float(i+1)/im.width(),float(j)/im.height());
            m_terrain.vertex( Point(i+1, 100.f*im(i+1, j).r, j) );

            m_terrain.normal( terrainNormal(im, i, j) );
            m_terrain.texcoord(float(i+1)/im.width(),float(j)/im.height());
            m_terrain.vertex( Point(i, 100.f*im(i, j).r, j) );
        }
        m_terrain.restart_strip();
    }
}



//**************************** Cube Map ***************************

void ViewerEtudiant::init_cubemap() {
    int i;
    float w = 1.0/4.0;
    float h = 1.0/3.0;

    static float pt[8][3]= { {1,1,1}, {-1,1,1}, {-1,1,-1}, {1,1,-1}, {1,-1,1}, {-1,-1,1}, {-1,-1,-1}, {1,-1,-1} };
    static int f[6][4]= { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
    static float n[6][3]= { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };

    m_cubemap = Mesh(GL_TRIANGLE_STRIP);

    for (i=0;i<6;i++)
    {
        switch(i) {
        case 0 :
            m_cubemap.normal(n[i][0], n[i][1], n[i][2]);
            m_cubemap.texcoord(2.0*w ,  1.0); // 0,0
            m_cubemap.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

            m_cubemap.texcoord(w , 1.0);  // 1,0
            m_cubemap.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

            m_cubemap.texcoord(2.0*w , 2.0*h);  // 0,1
            m_cubemap.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

            m_cubemap.texcoord(w , 2.0*h);  // 1,1
            m_cubemap.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );

            m_cubemap.restart_strip();
        break;

        case 1 :
            m_cubemap.normal(n[i][0], n[i][1], n[i][2]);

            m_cubemap.texcoord(2.0*w , h); // 0,0
            m_cubemap.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

            m_cubemap.texcoord(w , h);  // 1,0
            m_cubemap.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

            m_cubemap.texcoord(2.0*w , 0);  // 0,1
            m_cubemap.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

            m_cubemap.texcoord(w ,  0);  // 1,1
            m_cubemap.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );

            m_cubemap.restart_strip();
        break;

        case 2 :
            m_cubemap.normal(n[i][0], n[i][1], n[i][2]);

            m_cubemap.texcoord(w , 2.0*h); // 0,0
            m_cubemap.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

            m_cubemap.texcoord(0 , 2.0*h);  // 1,0
            m_cubemap.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

            m_cubemap.texcoord(w , h);  // 0,1
            m_cubemap.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

            m_cubemap.texcoord(0 ,  h);  // 1,1
            m_cubemap.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );

            m_cubemap.restart_strip();
        break;

        case 3 :
            m_cubemap.normal(n[i][0], n[i][1], n[i][2]);

            m_cubemap.texcoord(3.0*w ,  2.0*h); // 0,0
            m_cubemap.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

            m_cubemap.texcoord(2.0*w , 2.0*h);  // 1,0
            m_cubemap.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

            m_cubemap.texcoord(3.0*w , h);  // 0,1
            m_cubemap.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

            m_cubemap.texcoord(2.0*w , h);  // 1,1
            m_cubemap.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );

            m_cubemap.restart_strip();
        break;

        case 4 :
            m_cubemap.normal(n[i][0], n[i][1], n[i][2]);

            m_cubemap.texcoord(2.0*w ,  2.0*h); // 0,0
            m_cubemap.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

            m_cubemap.texcoord(w , 2.0*h);  // 1,0
            m_cubemap.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

            m_cubemap.texcoord(2.0*w , h);  // 0,1
            m_cubemap.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

            m_cubemap.texcoord(w , h);  // 1,1
            m_cubemap.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );

            m_cubemap.restart_strip();
        break;

        case 5:
            m_cubemap.normal(n[i][0], n[i][1], n[i][2]);

            m_cubemap.texcoord(1.0 ,  2.0*h); // 0,0
            m_cubemap.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

            m_cubemap.texcoord(3.0*w , 2.0*h);  // 1,0
            m_cubemap.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

            m_cubemap.texcoord(1.0 , h);  // 0,1
            m_cubemap.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

            m_cubemap.texcoord(3.0*w , h);  // 1,1
            m_cubemap.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );

            m_cubemap.restart_strip();
        break;
        }
    }
}



//**************************** Arbre ***************************

void ViewerEtudiant::init_billboard(){

    m_quad = Mesh(GL_TRIANGLE_STRIP);

    m_quad.normal(0, 0, 1);

    m_quad.texcoord(0,0);
    m_quad.vertex(-1, -1, 0);

    m_quad.texcoord(0,1);
    m_quad.vertex(1, -1, 0);

    m_quad.texcoord(1,0);
    m_quad.vertex(-1, 1, 0);

    m_quad.texcoord(1,1);
    m_quad.vertex(1, 1, 0);
}

void ViewerEtudiant::init_height_tree(const Image& im) {

    int k = im.width()-2;
    int j = im.height()-1;

    for(int i = 0 ; i < 100 ; i++  ){

        pos[i].x =(rand() % k + 1)*0.1;
        pos[i].z = (rand() % j + 1)*0.1 ;

        pos[i].y = (100.f * im(pos[i].x, pos[i].z).r +30 )*0.1 ;

    }

}



//**************************** Texture Animee ***************************

void ViewerEtudiant::init_textanime() {

    // Choix de la primitive OpenGL
    m_textureanimee = Mesh(GL_TRIANGLE_STRIP);

    // Vecteur normal a la face
    m_textureanimee.normal(0, 0, 1);

    m_textureanimee.texcoord(0 ,0);
    m_textureanimee.vertex(-1, -1, 0);

    m_textureanimee.texcoord(1.0/9.0, 0);
    m_textureanimee.vertex(1, -1, 0);

    m_textureanimee.texcoord(0, 1);
    m_textureanimee.vertex(-1, 1, 0);

    m_textureanimee.texcoord(1.0 / 9.0, 1);
    m_textureanimee.vertex(1, 1, 0);

 }




/*
 * Fonction dans laquelle les initialisations sont faites.
 */

int ViewerEtudiant::init()
{
    Viewer::init();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_REPEAT);

    m_camera.lookat( Point(0,0,0), 200 );


    /// Appel des fonctions init_votreObjet pour creer les Mesh

    init_cube();
    init_cone();
    init_cylindre();
    init_sphere();
    init_disque();
    init_triangle();
    init_drapeau();


    create_vertex_normal_vase();
    init_vase();


    // Calcul des coordonn?es des sommets et des normales
    create_vertex_normal_vase();
    // Cr?ation du Mesh ? partir des coordonn?es calcul?es
    init_vase();


    m_oceanAlti = read_image("data/data_extern/Water_001_DISP.png");
    init_ocean(m_ocean, m_oceanAlti);

    m_terrainAlti = read_image("data/data_extern/island.jpg");
    init_terrain(m_terrain, m_terrainAlti);


    init_cubemap();


    init_billboard();
    init_height_tree(m_terrainAlti);


    init_textanime();


    /// Chargement des textures

    tex_cube = read_texture(0, "data/mur.png" );
    tex_sphere = read_texture(0, "data/monde.jpg" );
    tex_cone = read_texture(0, "data/mur.png" );
    tex_cylindre = read_texture(0,"data/monde.jpg" );

    tex_ocean = read_texture(0,"data/data_extern/Water_COLOR.jpg");
    tex_terrain = read_texture(0,"data/data_extern/Lava.png");

    tex_billboard = read_texture(0,"data/data_extern/arbre1.png" );

    tex_cubemap =  read_texture(0,"data/data_extern/skybox.jpg");

    tex_feu =  read_texture(0,"data/fire.png");




    ///Animation

    m_animBateau.init(smart_path("data/animation/anim1.ani"));


    return 0;
}










/*
 * Exemple de definition de fonction permettant l affichage
 * de 'votreObjet' subissant la Transform T
 */

 void ViewerEtudiant::draw_disque(const Transform& T, unsigned int tex)
{
    gl.model(T);
    gl.texture(tex);
    gl.draw(m_disque);

}

 void ViewerEtudiant::draw_cone(const Transform& T, unsigned int tex)
{
    gl.model(T);
    gl.texture(tex);
    gl.draw(m_cone);

    Transform Tch = T * Translation(0,0,0);
    gl.model(Tch);
    gl.draw(m_disque);
}

 void ViewerEtudiant::draw_sphere(const Transform& T, unsigned int tex)
{
    gl.model(T);
    gl.texture(tex);
    gl.draw(m_sphere);


}

void ViewerEtudiant::draw_cube(const Transform& T, unsigned int tex)
{
    gl.model(T);
    gl.texture(tex);
    gl.draw(m_cube);

}

void ViewerEtudiant::draw_cylindre(const Transform& T, unsigned int tex)
{
    gl.model(T);
    gl.texture(tex);
    gl.draw( m_cylindre );

    // Disque du bas
    draw_disque(T * Translation( 0, -1, 0),tex);

    // Disque du haut
    draw_disque(T * Translation( 0, 1, 0)* Rotation( Vector(1,0,0), 180),tex);
}

void ViewerEtudiant::draw_triangle(const Transform& T)
{
    gl.model(T);
    gl.draw(m_triangle);

}

void ViewerEtudiant::draw_drapeau(const Transform& T)
{
    gl.model(T);
    gl.draw(m_drapeau);

}



void ViewerEtudiant::draw_avion(const Transform& T)
{
    draw_sphere(T* Translation(0,0,0)*Scale(0.5,2.5,0.5),0);

    draw_cube(T* Translation(1.8,0.3,0)*Scale(1.5,0.6,0.1),tex_cube);
    draw_cube(T* Translation(-1.8,0.3,0)*Scale(1.5,0.6,0.1),tex_cube);

    draw_cylindre(T* Translation(1.5,0.3,-0.3)*Scale(0.3,1,0.3),0);
    draw_cylindre(T* Translation(-1.5,0.3,-0.3)*Scale(0.3,1,0.3),0);

    draw_cube(T* Translation(0,-1.3,0.3)*Scale(0.05,0.2,0.3),tex_cube);

}

void ViewerEtudiant::draw_bateau(const Transform& T)
{

    draw_cube(T* Translation(0,0,0)*Scale(2.5,0.5,1),0);

    draw_cylindre(T* Translation(2.5,0.2,0)*Scale(1,0.7,1),0);
    draw_cube(T* Translation(1.9,0.7,0)*Scale(0.6,0.2,1),0);

    draw_cube(T* Translation(-0.3,0.5,0.975)*Scale(1.7,0.1,0.025),0);

    draw_cylindre(T* Translation(2.2,1.8,0)*Scale(0.1,1,0.1),0);
        draw_drapeau(T* Translation(2.2,1.8,0)*Scale(0.5,0.7,0.8)*Rotation(Vector(1,0,0),90)*Rotation(Vector(1,0,-1),180));

    draw_cylindre(T* Translation(0.2,2,0)*Scale(0.15,2,0.15),0);
        draw_drapeau(T* Translation(0.2,1.5,0)*Scale(0.7,0.7,1)*Rotation(Vector(1,0,0),90)*Rotation(Vector(1,0,-1),180));
        draw_drapeau(T* Translation(0.2,3,0)*Scale(0.5,0.7,0.8)*Rotation(Vector(1,0,0),90)*Rotation(Vector(1,0,-1),180));

    draw_cylindre(T* Translation(-2,2,0)*Scale(0.15,1.8,0.15),0);
        draw_drapeau(T* Translation(-2,1.5,0)*Scale(0.5,0.7,0.8)*Rotation(Vector(1,0,0),90)*Rotation(Vector(1,0,-1),180));
        draw_drapeau(T* Translation(-2,3,0)*Scale(0.4,0.7,0.6)*Rotation(Vector(1,0,0),90)*Rotation(Vector(1,0,-1),180));


    draw_cube(T* Translation(-0.3,0.5,-0.975)*Scale(1.7,0.1,0.025),0);

    draw_cube(T* Translation(-2.1,0.5,0)*Scale(0.4,0.2,1),0);
    draw_triangle(T* Translation(-2.5,-0.5,-1)*Scale(1,1.2,1) *Rotation(Vector(1,0,0),180));




}



void ViewerEtudiant::draw_vase(const Transform& T){
    gl.model(T); // Applique Transform T
    gl.draw(m_vase); // Affichage du Mesh
}





void ViewerEtudiant::draw_billboard(const Transform& T){

    draw_quadcross(T* Translation(Vector(0, 0, 0)) * RotationY(90));
    draw_quadcross(T* Translation(Vector(0,0,0)));
}

void ViewerEtudiant::draw_quadcross(const Transform& T){

    gl.alpha(0.3);
    gl.texture(tex_billboard);
    //Activation de la transparence sur le 1er quad
    gl.alpha(0.3);

    gl.model(T * RotationZ(90));
    gl.draw(m_quad);

    gl.alpha();
    ///Activation de la transparence sur le 2eme quad
    gl.alpha(0.3);

    gl.model(T * RotationZ(90) * RotationX(180));
    gl.draw(m_quad);

    gl.alpha();

}




void ViewerEtudiant::draw_ocean(const Transform& T, unsigned int tex){

    gl.model( T );
    gl.texture(tex);
    gl.draw( m_ocean );

}

void ViewerEtudiant::draw_terrain(const Transform& T, unsigned int tex){
    gl.model( T );
    gl.texture(tex);
    gl.draw( m_terrain );
}



void ViewerEtudiant::draw_cubemap(const Transform& T, unsigned int tex)
{
    gl.model(T);
    gl.texture(tex);
    gl.draw(m_cubemap);

}




void ViewerEtudiant::draw_feu(const Transform& T){

    draw_quadfeu(T* Translation(Vector(0, 0, 0)) * RotationY(90));
    draw_quadfeu(T* Translation(Vector(0,0,0)));
}

void ViewerEtudiant::draw_quadfeu(const Transform& T){

    gl.alpha(0.3);
    gl.texture(tex_feu);
    gl.model(T);
    gl.draw(m_textureanimee);
    gl.model(T * RotationY(180));
    gl.draw(m_textureanimee);
    gl.alpha();

}




/*
 * Fonction dans laquelle les appels pour les affichages sont effectues.
 */
int ViewerEtudiant::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_LIGHTING);
    gl.lighting(true);

    manageCameraLight();

    gl.model(Identity());
    gl.camera(m_camera);


    gl.light( Point(30, 60, -80), White() );

    gl.lighting(true);

    //draw_cube(Translation(0,0,0)*Scale(1,1,1),tex_cube);
    //draw_cylindre(Translation(-2,0,0)*Scale(0.5,0.5,0.5)*Rotation(Vector(1,0,0),180),tex_cylindre);
    //draw_cone(Translation(0,0,0)*Scale(0.5,0.5,0.5),tex_cone);
    //draw_sphere(Translation(0,0,0)*Scale(0.5,0.5,0.5)*Rotation(Vector(1,0,0),180),tex_sphere);
    //draw_avion(Translation(0,0,0)*Scale(1,1,1));
    //draw_vase(Translation(0,4,0)*Scale(3,3,3));


    draw_bateau(Transform_Bateau*Scale(1,1,1)*Rotation(Vector(0,1,0),180));

    for(int k = 0 ; k < 30 ; k++  ){
        if (pos[k].y > 0.4) {
            draw_billboard(Translation(pos[k].x-50 , pos[k].y , pos[k].z-50)*Scale(2,2,2));
        }
    }


    draw_cubemap(Translation(0,0,0)*Scale(100,100,100),tex_cubemap);

    draw_ocean(Translation(-100,0,-100)*Scale(0.2,0.2,0.2),tex_ocean);
    draw_terrain(Translation(-50,-0.2,-50)*Scale(0.1,0.1,0.1),tex_terrain);

    draw_feu(Translation(-24,11,-5)*Scale(15,15,15));

    return 1;

}


















/*
 * Fonction dans laquelle les mises a jours sont effectuees.
 */
int ViewerEtudiant::update( const float time, const float delta )
{
    // time est le temps ecoule depuis le demarrage de l'application, en millisecondes,
    // delta est le temps ecoule depuis l'affichage de la derniere image / le dernier appel a draw(), en millisecondes.


    // **************** TEXTURE ANIMEE ************************
    float premierTemps = time / 150;
    int secondTemps = int(premierTemps);


    compteurTps = secondTemps;

    int nt = compteurTps % 9;

    m_textureanimee.texcoord(0, nt * (1.0 / 9.0) , 0 );
    m_textureanimee.texcoord(1, nt * (1.0 / 9.0)+ (1.0/9.0),0);
    m_textureanimee.texcoord(2, nt * (1.0 / 9.0) , 1);
    m_textureanimee.texcoord(3, nt * (1.0 / 9.0) + (1.0 / 9.0), 1);


    // **************** ANIMATION ************************

        float Temps2 = time/1000.0;
    int Temps1 = int(Temps2);

    int iTemps = Temps1 % m_animBateau.nb_points();
    int iTemps_suiv = (Temps1+1) % m_animBateau.nb_points();
    int iTemps_suiv_suiv = (iTemps_suiv + 1) % m_animBateau.nb_points();

    Point p0 = m_animBateau[iTemps];
    Point p1 = m_animBateau[iTemps_suiv];
    Point p2 = m_animBateau[iTemps_suiv_suiv];

    float poids = Temps2 - Temps1;

    Vector pos_suiv = Vector(p1) + (Vector(p2) - Vector(p1)) * poids;
    Vector pos = Vector(p0) + (Vector(p1) - Vector(p0)) * poids;

    Vector dir = normalize(pos_suiv - pos);
    Vector up(0,1,0);
    Vector codir = cross(dir, up);

    Transform_Bateau = Transform(dir, up, codir, pos);

    Transform_Bateau = Transform(dir.x, up.x, codir.x, pos.x,
                        dir.y, up.y, codir.y, pos.y,
                        dir.z, up.z, codir.z, pos.z,
                        0    , 0   , 0      , 1);



    return 0;
}


/*
 * Constructeur.
 */

ViewerEtudiant::ViewerEtudiant() : Viewer()
{

}


/*
 * Programme principal.
 */
int main( int argc, char **argv )
{
    ViewerEtudiant v;
    v.run();
    return 0;
}
