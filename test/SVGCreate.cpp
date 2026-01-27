#include "../include/Grawink.h"

int main(void){

    // Creaation d'un Canvas avec une largeur de 1500, une hauteur de 1000 et un gris clair transparent comme couleur de fond
    GrawEditor& editor = GrawEditor::GetEditor(1500, 1000, Color(1, 1, 1, float(0.2)));

    // Creation de multiple formes
    editor.Add<Rectangle>("Rectangle 1", Point(100, 300), 100, 50, Color(1, 0, 0, 1), Color(0, 1, 0, 1));
    editor.Add<Rectangle>("Rectangle 2", Point(200, 200), 100, 50, Color(1, 0, 0, 1), Color(0, 1, 0, 1));
    editor.Add<Disc>("Disc 1", Point(300, 300), Color(1, 0, 0, 1), Color(0, 1, 0, 1), 50);
    editor.Add<Stroke>("Stroke 1", Point(400, 400), Point(1000, 1000), Color(1, 0, 0, 1));
    editor.Add<Ellipse>("Ellipse 1", Point(400, 400), Color(1, 0, 0, 1), Color(0, 1, 0, 1), 50, 100);
    editor.Add<Triangle>("Triangle 1", Point(500, 500), Point(600, 600), Point(500, 700), Color(1, 0, 0, 1), Color(0, 1, 0, 1));
    editor.Add<Polygon>("Polygon 1", Color(1, 0, 0, 1), Color(0, 1, 0, 1));

    // Rajout de point dans le polygon
    editor.AddPointPolygon("Polygon 1", Point(100, 100));
    editor.AddPointPolygon("Polygon 1", Point(110, 100));
    editor.AddPointPolygon("Polygon 1", Point(120, 120));
    editor.AddPointPolygon("Polygon 1", Point(130, 130));
    editor.AddPointPolygon("Polygon 1", Point(200, 140));

    // Rajout de texte et de carré
    editor.Add<Text>("Text 1", "Hello World", "Arial", 12, 1, Color(1, 0, 0, 1), Color(0, 1, 0, 1), Point(800, 800));
    editor.Add<Square>("Square 1", Point(900, 900), 50, Color(1, 0, 0, 1), Color(0, 1, 0, 1));

    // Selection de toutes les formes
    editor.Select(GrawEditor::ShapeType::All);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#1.svg", true);

    // Réalise 3 undo
    editor.Undo(3);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#2.svg", true);

    // Réalise 2 redo
    editor.Redo(2);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#3.svg", true);

    // Réalise encore 1 redo
    editor.Redo(1);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#4.svg", true);

    // Delete 1 rectangle
    editor.Delete("Rectangle 1");

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#5.svg", true);

    // Réalise un undo
    editor.Undo(1);

    // Deselctionne toutes les formes
    editor.Deselect(GrawEditor::ShapeType::All);

    // Selectionne le rectangle
    editor.Select(GrawEditor::ShapeType::Rectangle);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#6.svg", true);

    // Selectionne toutes les formes
    editor.Select(GrawEditor::ShapeType::All);

    // Change la couleur de fond du canvas
    editor.Repaint(Color(1, 124, 1, float(0.3)));

    // Change la couleur de toute les formes de facon arc en ciel
    editor.Fill("Rectangle 1", Color(255, 0, 0, float(0.3)));
    editor.Contour("Rectangle 1", Color(0, 0, 0, float(1)));
    editor.Fill("Rectangle 2", Color(0, 255, 0, float(0.3)));
    editor.Contour("Rectangle 2", Color(0, 0, 0, float(1)));
    editor.Fill("Disc 1", Color(0, 0, 255, float(0.3)));
    editor.Contour("Disc 1", Color(0, 0, 0, float(1)));
    editor.Fill("Ellipse 1", Color(255, 255, 0, float(0.3)));
    editor.Contour("Ellipse 1", Color(0, 0, 0, float(1)));
    editor.Fill("Triangle 1", Color(0, 255, 255, float(0.3)));
    editor.Contour("Triangle 1", Color(0, 0, 0, float(1)));
    editor.Fill("Text 1", Color(255, 0, 255, float(0.3)));
    editor.Contour("Text 1", Color(0, 0, 0, float(1)));
    editor.Fill("Square 1", Color(255, 255, 255, float(0.3)));
    editor.Contour("Square 1", Color(0, 0, 0, float(1)));
    editor.Fill("Polygon 1", Color(126, 23, 123, float(0.3)));
    editor.Contour("Polygon 1", Color(0, 0, 0, float(1)));

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#7.svg", true);

    // Translate des 2 rectangles
    editor.Translate("Rectangle 2", 100, 100);
    editor.Translate("Rectangle 1", 100, 100);
    // Rotate du triangle
    editor.Rotate("Triangle 1", 90);
    // Scale du texte et du polygon
    editor.Scale("Text 1", 2);
    editor.Scale("Polygon 1", 2);
    editor.Scale("Square 1", 2);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#8.svg", true);

    // Undo des 5 dernières actions
    editor.Undo(5);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#9.svg", true);

    // Redo des 5 dernières actions
    editor.Redo(1);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#10.svg", true);

    editor.Rotate("Polygon 1", 90);

    // Crop du canvas pour que la forme du carré sorte du canvas (Le crop est définitif et ne peut pas être annulé, les formes qui sortent du canvas sont supprimées et ne peuvent pas être récupérées)
    editor.Crop(900, 1000);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#11.svg", true);

    // undo
    editor.Undo(1);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#12.svg", true);

    // Redo
    editor.Redo(1);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#13.svg", true);

    // undo
    editor.Undo(1);

    // Affichage des formes selectionnées
    editor.Print();

    // Export des formes selectionnées dans un fichier SVG
    editor.ExportSVG("out/svg/SvgCreate#14.svg", true);

    return 0;
}