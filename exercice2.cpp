#include <iostream>
#include <vector>
#include <memory>   
#include <cmath>   

using namespace std;
struct Vec3 {
    float x, y, z;
    Vec3(float px = 0.0f, float py = 0.0f, float pz = 0.0f) {
        x = px;
        y = py;
        z = pz;
    }
};
class Lumiere {
public:
    virtual ~Lumiere() {
    }
    virtual float intensite(const Vec3& position) = 0;
};
class LumiereDirectionnelle : public Lumiere {
private:
    Vec3 direction;
    float intensiteBase;

public:
    LumiereDirectionnelle(Vec3 dir, float intens) {
        direction = dir;
        intensiteBase = intens;
    }

    float intensite(const Vec3& position) override {
        cout << "  [Lumiere Directionnelle] Intensite constante : " << intensiteBase << endl;
        return intensiteBase;
    }
};
class LumierePonctuelle : public Lumiere {
private:
    Vec3 positionLumiere;
    float puissance;

public:
    LumierePonctuelle(Vec3 pos, float puiss) {
        positionLumiere = pos;
        puissance = puiss;
    }

    float intensite(const Vec3& position) override {
        float distance = sqrt(pow(position.x - positionLumiere.x, 2) +
                              pow(position.y - positionLumiere.y, 2) +
                              pow(position.z - positionLumiere.z, 2));
        
        float attenu = puissance / (1.0f + 0.1f * distance);
        cout << "  [Lumiere Ponctuelle] Distance au point = " << distance << " -> Intensite = " << attenu << endl;
        return attenu;
    }
};
class LumiereSpot : public Lumiere {
private:
    Vec3 positionSpot;
    Vec3 directionSpot;
    float puissanceMax;

public:
    LumiereSpot(Vec3 pos, float puiss) {
        positionSpot = pos;
        puissanceMax = puiss;
    }

    float intensite(const Vec3& position) override {
        float distance = sqrt(pow(position.x - positionSpot.x, 2) +
                              pow(position.y - positionSpot.y, 2));
        
        float attenuSpot = puissanceMax / (1.0f + 0.2f * distance);
        cout << "  [Lumiere Spot] Calcul projecteur -> Intensite = " << attenuSpot << endl;
        return attenuSpot;
    }
};
float calculerEclairage(const vector<unique_ptr<Lumiere>>& sceneLumieres, const Vec3& point) {
    float intensiteTotale = 0.0f;
    
    for (size_t i = 0; i < sceneLumieres.size(); i++) {
        intensiteTotale += sceneLumieres[i]->intensite(point);
    }
    
    return intensiteTotale;
}

int main() {
    cout << "Test du Moteur d'Eclairage 3D" << endl << endl;
    vector<unique_ptr<Lumiere>> scene;
    scene.push_back(make_unique<LumiereDirectionnelle>(Vec3(0.0f, -1.0f, 0.0f), 1.5f));
    scene.push_back(make_unique<LumierePonctuelle>(Vec3(5.0f, 5.0f, 5.0f), 10.0f));
    scene.push_back(make_unique<LumiereSpot>(Vec3(0.0f, 10.0f, 0.0f), 8.0f));

    Vec3 pointTest1(1.0f, 2.0f, 1.0f);
    Vec3 pointTest2(4.0f, 1.0f, 2.0f);

    cout << "Calcul d'eclairage pour le Point 1 (1, 2, 1)" << endl;
    float eclairage1 = calculerEclairage(scene, pointTest1);
    cout << "-> Eclairage total recu au Point 1 : " << eclairage1 << "\n" << endl;

    cout << "Calcul d'eclairage pour le Point 2 (4, 1, 2)" << endl;
    float eclairage2 = calculerEclairage(scene, pointTest2);
    cout << "-> Eclairage total recu au Point 2 : " << eclairage2 << endl;

    cout << "\nFin du programme" << endl;
    return 0;
}