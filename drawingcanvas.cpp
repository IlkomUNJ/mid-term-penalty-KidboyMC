#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");
    initializeDetectors();
}

// Mendefinisikan matriks 3x3 untuk garis horizontal, vertikal, dan diagonal, lalu menyimpannya ke dalam m_segment_detectors
void DrawingCanvas::initializeDetectors(){
    // 1. Garis Horizontal
    bool h_line[3][3] = {{0,0,0}, {1,1,1}, {0,0,0}};
    m_segment_detectors.append(CustomMatrix(h_line));

    // 2. Garis Vertikal
    bool v_line[3][3] = {{0,1,0}, {0,1,0}, {0,1,0}};
    m_segment_detectors.append(CustomMatrix(v_line));

    // 3. Garis Diagonal (kanan bawah)
    bool d1_line[3][3] = {{1,0,0}, {0,1,0}, {0,0,1}};
    m_segment_detectors.append(CustomMatrix(d1_line));

    // 4. Garis Diagonal (kanan atas)
    bool d2_line[3][3] = {{0,0,1}, {0,1,0}, {1,0,0}};
    m_segment_detectors.append(CustomMatrix(d2_line));
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    m_detected_segments.clear();
    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::paintLines(){
    /* Todo
     * Implement lines drawing per even pair
    */

    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection(){
    // Mengosongkan hasil lama dan mengambil kanvas
    m_detected_segments.clear();
    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    cout << "Starting Segment Detection" << endl;
    cout << "Image size: " << image.width() << "x" << image.height() << endl;

    // Menggeser window ke setiap piksel (x,y) di gambar
    for(int y = 1; y < image.height() - 1; y++){ // Bergerak dari atas ke bawah
        for(int x = 1; x < image.width() - 1; x++){ // Bergerak dari kiri ke kanan
            // Melihat piksel (x,y) dan 8 tetangganya
            bool local_window[3][3] = {{false}};
            for(int m = -1; m <= 1; m++){
                for(int n = -1; n <= 1; n++){
                    // Cek warna piksel tetangga
                    QRgb rgbValue = image.pixel(x + n, y + m);
                    // Jika warnanya bukan putih (0xffffffff), tandai sebagai true (1)
                    local_window[m + 1][n + 1] = (rgbValue != 0xffffffff);
                }
            }

            // Mengubah window menjadi objek CustomMatrix
            CustomMatrix current_mat(local_window);

            if (!current_mat.isEmpty()) {
                cout << "Pattern at (" << x << ", " << y << "):" << endl;
                current_mat.print();
            }

            // Bandingkan pola saat ini dengan semua pola ideal (detector)
            for (const CustomMatrix& detector : std::as_const(m_segment_detectors)) {
                if (current_mat == detector) {
                    // Jika cocok, simpan koordinat tengah (x,y) dan berhenti mencari di titik ini
                    m_detected_segments.append(QPoint(x, y));
                    break; // Lanjut ke piksel berikutnya
                }
            }
        }
    }

    cout << m_detected_segments.size() << " segment candidates found." << endl;
    // Gambar ulang kanvas dengan hasil yang baru
    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up the pen and brush for drawing the points
    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if(isPaintLinesClicked){
        cout << "paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4); // 4-pixel wide line
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

        // Set the painter's pen to our custom pen.
        painter.setPen(pen);

        for(int i=0;i<m_points.size()-1;i+=2){
            //cout << m_points[i].x() << endl;
            painter.drawLine(m_points[i], m_points[i+1]);
        }
        isPaintLinesClicked = false;

        //return painter pen to blue
        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }

    // Dipanggil secara otomatis setiap kali update() dijalankan
    if (!m_detected_segments.isEmpty()) { // Hanya jalankan jika ada sesuatu yang ditemukan
        QPen purplePen(QColor(128, 0, 128));
        purplePen.setWidth(1);
        painter.setPen(purplePen);
        painter.setBrush(Qt::NoBrush);

        // Loop untuk setiap titik tengah segmen yang ditemukan
        for (const QPoint& center : std::as_const(m_detected_segments)) {
            // Gambar persegi 3x3 di sekitar titik tengah tersebut
            painter.drawRect(center.x() - 1, center.y() - 1, 3, 3);
        }
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}


