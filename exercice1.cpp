#include <iostream>
#include <string>

using namespace std;
class SortieAudio {
public:
    virtual ~SortieAudio() {
        cout << "[DESTRUCTEUR] Liberation d'une sortie audio." << endl;
    }
    virtual void ouvrir() = 0;
    virtual void jouer(const string& son) = 0;
    virtual void fermer() = 0;
};
class HautParleur : public SortieAudio {
public:
    void ouvrir() override {
        cout << "[Haut-Parleur] Ouverture du canal audio integre." << endl;
    }

    void jouer(const string& son) override {
        cout << "[Haut-Parleur] Diffusion du son : " << son << endl;
    }

    void fermer() override {
        cout << "[Haut-Parleur] Fermeture du canal audio." << endl;
    }
};
class CasqueBT : public SortieAudio {
public:
    void ouvrir() override {
        cout << "[Casque BT] Connexion sans fil au casque Bluetooth..." << endl;
    }

    void jouer(const string& son) override {
        cout << "[Casque BT] Diffusion audio haute definition : " << son << endl;
    }

    void fermer() override {
        cout << "[Casque BT] Deconnexion du peripherique sans fil." << endl;
    }
};
class SortieHDMI : public SortieAudio {
public:
    void ouvrir() override {
        cout << "[Sortie HDMI] Initialisation du flux numerique ecran/TV..." << endl;
    }

    void jouer(const string& son) override {
        cout << "[Sortie HDMI] Transmission du flux multimédia : " << son << endl;
    }

    void fermer() override {
        cout << "[Sortie HDMI] Coupure du signal HDMI." << endl;
    }
};
void tester(SortieAudio* sortie) {
    if (sortie != nullptr) {
        sortie->ouvrir();
        sortie->jouer("Piste_Audio_01.mp3");
        sortie->fermer();
    }
}

int main() {
    cout << "Test du Systeme de Gestion Audio" << endl;
    const int taille = 3;
    SortieAudio* peripheriques[taille];
    peripheriques[0] = new HautParleur();
    peripheriques[1] = new CasqueBT();
    peripheriques[2] = new SortieHDMI();

    for (int i = 0; i < taille; i++) {
        tester(peripheriques[i]);
    }

    cout << "\nNettoyage de la memoire" << endl;
    for (int i = 0; i < taille; i++) {
        delete peripheriques[i];
    }

    cout << "\nFin du programme" << endl;
    return 0;
}