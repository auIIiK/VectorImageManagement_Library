#include "../include/Grawink.h"


int main(void){

    GrawEditor& editor = GrawEditor::GetEditor(1000, 1000, Color(1, 1, 1, 0.2f));
    editor.LoadSVG("out/svg/SvgCreate#7.svg");

    editor.Select(GrawEditor::ShapeType::All);

    editor.Print();

    // Exportation en image des formes selectionné 
    // La consommation mémoire est très élevée pour les fichiers PPM et PAM ainsi que la durée d'exécution
    // Cela est due au fait que nous parcouront toutes les forme par pixel pour les couleur a mettre dans l'image au format binaire 
    // Pour resoudre cela nous devons utiliser du multithread
    // Vu le temps d'execution je conseille d'utiliser soit l'un ou l'autre

    // De plus l'exportation ne fonctionne pas pour les textes car il sont considéré comme un rectangle et moi ma méthode fait pixel par pixel sauf que j'ai pas les points du texte avec certitude

    // Exportation en ppm donc sans transparence

    editor.ExportPPM("out/ExportPPM#7.ppm");

    // Exportation en pam donc avec transparence mais ce format est moin généraliser.
    // Si vous ne pouvez pas l'ouvrir vous pouvez le convertir en png avec la commande convert ...pam ...png 
    // Cette commande se trouve dans la blibliothèque ImageMagick
    // Telechargement de cette blibliothèque sur mac "brew install imagemagick"
    // Telechargement de cette blibliothèque sur linux "sudo apt-get install imagemagick"

    editor.ExportPAM("out/ExportPAM#7.pam");


    return 0;


}