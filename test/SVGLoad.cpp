#include "../include/Grawink.h"


int main(void){

    // Charge un fichier SVG
    GrawEditor& editor = GrawEditor::GetEditor(1000, 1000, Color(1, 1, 1, float(0.2)));
    editor.LoadSVG("out/svg/SvgCreate#7.svg");

    // Selctionne toutes les formes
    editor.Select(GrawEditor::ShapeType::All);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgLoad#1.svg", true);

    editor.Undo(1);

    editor.ExportSVG("out/svg/SvgLoad#2.svg", true);

    editor.Rotate("line1", 30);

    editor.ExportSVG("out/svg/SvgLoad#3.svg", true);

    editor.Translate("line1", 100, 100);

    editor.ExportSVG("out/svg/SvgLoad#4.svg", true);

    editor.Scale("line1", 1.25);
    editor.Contour("line1",Color(167, 1, 1, 1));

    editor.Print();

    editor.ExportSVG("out/svg/SvgLoad#5.svg", true);

    return 0;

}