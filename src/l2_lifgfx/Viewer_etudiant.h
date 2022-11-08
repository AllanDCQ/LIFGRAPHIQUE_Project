
#ifndef VIEWER_ETUDIANT_H
#define VIEWER_ETUDIANT_H

#include "Viewer.h"

#define MAXPTS 100
const int vase_NBPT = 10;
const int vase_NBROT = 20;


class ViewerEtudiant : public Viewer
{
public:
    ViewerEtudiant();

    int init();
    int render();
    int update( const float time, const float delta );

protected:

    /* -----------------------------------------
     Pour creer un nouvel objet vous devez :

     1. declarer ici dans le fichier Viewer_etudiant.h
     le Mesh,
     la texture si besoin,
     une fonction 'init_votreObjet'
     une fonction 'draw_votreObjet(const Transform& T)'

     --- Rq : regarder comment cela est effectue dans le fichier Viewer.h


     2. Appeler la fonction 'init_votreObjet' dans la fonction 'init' du Viewer_etudiant.cpp
     --- Rq : regarder comment cela est effectue dans le fichier Viewer.cpp


     3. Appeler la fonction 'draw_votreObjet' dans la fonction 'render' du Viewer_etudiant.cpp
     --- Rq : regarder comment cela est effectue dans le fichier Viewer.cpp

      ----------------------------------------- */


    /// Declaration des Mesh

    Mesh m_cube;
    Mesh m_disque;
    Mesh m_sphere;
    Mesh m_cone;
    Mesh m_cylindre;
    Mesh m_triangle;
    Mesh m_drapeau;
    Mesh m_quad;

    Mesh m_vase;

    Mesh m_textureanimee;

    int i;
    int j;

    int compteurTps;


    Point pos[MAXPTS];
    Point vase_p[];
    Point vase_v[vase_NBROT][vase_NBPT];
    Vector vase_vn[vase_NBROT][vase_NBPT];



    Mesh m_ocean;
    Image m_oceanAlti;
    Vector oceanNormal(const Image& im,const int i, const int j);

    Mesh m_terrain;
    Image m_terrainAlti;
    Vector terrainNormal(const Image& im,const int i, const int j);

    Mesh m_cubemap;


    /// Declaration des Textures

    GLuint tex_cube;
    GLuint tex_disque;
    GLuint tex_cone;
    GLuint tex_sphere;
    GLuint tex_cylindre;

    GLuint tex_billboard;

    GLuint tex_ocean;
    GLuint tex_terrain;

    GLuint tex_cubemap;

    GLuint tex_feu;


    /// Declaration des fonction de creation de Mesh du type init_votreObjet()

    void init_cube();
    void init_disque();
    void init_cone();
    void init_sphere();
    void init_cylindre();
    void init_triangle();
    void init_drapeau();

    void init_vase();
    int create_vertex_normal_vase();

    void init_billboard();

    void init_ocean(Mesh& m_ocean, const Image& im);
    void init_terrain(Mesh& m_terrain, const Image& im);

    void init_height_tree(const Image& im);

    void init_cubemap();

    void init_textanime();




    /// Declaration des fonctions draw_votreObjet(const Transform& T)


    void draw_disque(const Transform& T, unsigned int tex);
    void draw_cylindre(const Transform& T, unsigned int tex);
    void draw_cube(const Transform& T, unsigned int tex);
    void draw_cone(const Transform& T, unsigned int tex);
    void draw_sphere(const Transform& T, unsigned int tex);
    void draw_triangle(const Transform& T);
    void draw_drapeau(const Transform& T);

    void draw_avion(const Transform& T);
    void draw_bateau(const Transform& T);

    void draw_vase(const Transform& T);

    void draw_billboard(const Transform& T);
    void draw_quadcross(const Transform& T);

    void draw_ocean(const Transform& T,unsigned int tex);
    void draw_terrain(const Transform& T,unsigned int tex);

    void draw_cubemap(const Transform& T,unsigned int tex);


    void draw_feu(const Transform& T);
    void draw_quadfeu(const Transform& T);




    /// Animation

    Transform Transform_Bateau;
    AnimationCurve m_animBateau;


};






#endif
