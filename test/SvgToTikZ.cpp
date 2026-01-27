#include "../include/Grawink.h"


int main(void){

    GrawEditor& editor = GrawEditor::GetEditor(1000, 1000, Color(1, 1, 1, float(0.2)));
    editor.LoadSVG("out/svg/SvgCreate#7.svg");

    editor.Select(GrawEditor::ShapeType::All);

    editor.Print();

    // Exportation des formes selectionnées dans un fichier latex TikZ
    editor.ExportTikZ("out/TikZ/SvgLoad#7.tex");

    return 0;

}