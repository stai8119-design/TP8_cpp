#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
class Plugin {
public:
    virtual ~Plugin() {
    }
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;
    static unique_ptr<Plugin> creerPlugin(const string& type);
};
class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override {
        return "Correcteur Orthographique";
    }

    string traiter(const string& texte) override {
        string resultat = texte;
        size_t pos = resultat.find("bcp");
        if (pos != string::npos) {
            resultat.replace(pos, 3, "beaucoup");
        }
        pos = resultat.find("akeur");
        if (pos != string::npos) {
            resultat.replace(pos, 5, "acteur");
        }
        return resultat;
    }
};
class TraducteurAnglais : public Plugin {
public:
    string nom() const override {
        return "Traducteur Anglais";
    }

    string traiter(const string& texte) override {
        string resultat = texte;
        
        size_t pos = resultat.find("bonjour");
        if (pos != string::npos) {
            resultat.replace(pos, 7, "hello");
        }
        pos = resultat.find("monde");
        if (pos != string::npos) {
            resultat.replace(pos, 5, "world");
        }
        
        return resultat;
    }
};
class AnalyseurStyle : public Plugin {
public:
    string nom() const override {
        return "Analyseur de Style";
    }

    string traiter(const string& texte) override {
        string resultat = texte;
        if (resultat.length() > 30) {
            resultat += " [Note Style : Phrase un peu longue detectee.]";
        } else {
            resultat += " [Note Style : Longueur correcte.]";
        }
        return resultat;
    }
};
unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {
    if (type == "correcteur") {
        return make_unique<CorrecteurOrthographique>();
    } else if (type == "traducteur") {
        return make_unique<TraducteurAnglais>();
    } else if (type == "analyseur") {
        return make_unique<AnalyseurStyle>();
    } else {
        return nullptr;
    }
}

int main() {
    cout << "Test de l'Editeur de Texte Extensible" << endl << endl;
    string texteSaisi = "bonjour tout le monde. le projet akeiur avance bcp.";
    cout << "Texte original saisi :\n\"" << texteSaisi << "\"\n" << endl;
    vector<unique_ptr<Plugin>> pluginsCharges;
    pluginsCharges.push_back(Plugin::creerPlugin("correcteur"));
    pluginsCharges.push_back(Plugin::creerPlugin("traducteur"));
    pluginsCharges.push_back(Plugin::creerPlugin("analyseur"));

    cout << "Debut du traitement progressif par les plugins" << endl;
    string texteCourant = texteSaisi;
    for (size_t i = 0; i < pluginsCharges.size(); i++) {
        if (pluginsCharges[i] != nullptr) {
            texteCourant = pluginsCharges[i]->traiter(texteCourant);
            
            cout << "\n[Etape " << (i + 1) << "] Applique par : " << pluginsCharges[i]->nom() << endl;
            cout << "=> Texte resultat : \"" << texteCourant << "\"" << endl;
        }
    }

    cout << "\nFin du programme" << endl;
    return 0;
}