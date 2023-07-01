#include "bezier_path.h"

#include <QJsonArray>
#include "utility.h"

#include <QPixmap>
#include <QPainter>

namespace eao {

namespace {
const QString closed_key = "c";
const QString in_points_key = "i";
const QString out_points_key = "o";
const QString vertices_key = "v";
}

BezierPath::~BezierPath()
{
}

BezierPath::BezierPath(const CurveVertex &vertex)
{
    m_elements.append(PathElement(0.0, vertex));
}

void BezierPath::move_to_start_point(const CurveVertex &vertex)
{
    m_elements.clear();
    m_elements.append(PathElement(0.0, vertex));
    m_length = 0;
}

void BezierPath::add_vertex(const CurveVertex &vertex)
{
    if (m_elements.size())
    {
        auto last = m_elements.last();
        add_element(last.path_element_to(vertex));
    }
    else
    {
        add_element(PathElement(0, vertex));
    }
}

void BezierPath::close()
{
    m_closed = true;
}

void BezierPath::add_element(const PathElement &element)
{
    m_elements.append(element);
    m_length += element.m_length;
}

void BezierPath::decode(const QJsonValue &in_value)
{
    auto in_obj = in_value.toObject();
    m_closed = in_obj.value(closed_key).toBool();
    auto vertices_array = in_obj.value(vertices_key).toArray();
    auto in_points_array = in_obj.value(in_points_key).toArray();
    auto out_points_array = in_obj.value(out_points_key).toArray();

    Q_ASSERT(vertices_array.size() == in_points_array.size());
    Q_ASSERT(out_points_array.size() == in_points_array.size());
    int size = vertices_array.size();
    if (!size)
        return;

    auto first_vertex = CurveVertex::from_relative(json_to_point(vertices_array.at(0)),
                                             json_to_point(in_points_array.at(0)),
                                             json_to_point(out_points_array.at(0)));

    auto previous_element = PathElement(0, first_vertex);

    QList<PathElement> decoded_elements;
    decoded_elements.reserve(size);
    decoded_elements.append(previous_element);

    double total_length = 0;
    for (int i = 1; i < size; ++i)
    {
        auto vertex = CurveVertex::from_relative(json_to_point(vertices_array.at(i)),
                                                 json_to_point(in_points_array.at(i)),
                                                 json_to_point(out_points_array.at(i)));

        const auto path_element = previous_element.path_element_to(vertex);
        decoded_elements.append(path_element);
        total_length += path_element.m_length;
        previous_element = path_element;
    }

    if (m_closed)
    {
        auto close_element = previous_element.path_element_to(first_vertex);
        decoded_elements.append(close_element);
        total_length += close_element.m_length;
    }

    m_length = total_length;
    m_elements = decoded_elements;

//    QPixmap pix(800, 800);
//    pix.fill(Qt::transparent);
//    QPainter painter(&pix);
//    painter.translate(400, 400);
//    painter.drawPath(path());

//    static int count = 0;
//    pix.save(QString("/home/sanju/file_%1.png").arg(count++));
}

const QPainterPath &BezierPath::path() const
{
    if (m_path.isEmpty())
    {
        auto el_size = m_elements.size();
        if (el_size)
        {
            auto prev_el = m_elements.first();
            m_path.moveTo(prev_el.m_vertex.m_point);
            for (int i = 1; i < el_size; ++i)
            {
                auto el = m_elements[i];

                if (prev_el.m_vertex.out_relative_tangent().isNull() and el.m_vertex.in_relative_tangent().isNull())
                {
                    m_path.lineTo(el.m_vertex.m_point);
                }
                else
                {
                    m_path.cubicTo(prev_el.m_vertex.m_out_point, el.m_vertex.m_in_point, el.m_vertex.m_point);
                }

                prev_el = el;
            }

            if (m_closed)
                m_path.closeSubpath();
        }
    }

    return m_path;
}

}

