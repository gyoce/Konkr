#ifndef KONKR_POPUPWIDGET_HPP
#define KONKR_POPUPWIDGET_HPP

#include "Engine/Ui/Gui.hpp"

#include <chrono>
#include <queue>

#include "Konkr/Utils/Constants.hpp"

struct PopupData
{
    std::string message;
    Color text_color{Color::White};
    Color background_color{0, 0, 0, 200};
    float duration_seconds{constants::default_total_duration};
    float fade_duration{constants::default_fade_duration};
};

class PopupWidget final : public GuiPanel
{
public:
    PopupWidget();

    void show_popup(const PopupData& data);
    void clear();

    void update() override;

    using SP = std::shared_ptr<PopupWidget>;

private:
    void start_next_popup();
    void hide_current_popup();
    void apply_fade_effect(float fade_progress);

    GuiText::SP m_message_label;
    std::queue<PopupData> m_popup_queue;
    PopupData m_current_popup;
    bool m_is_showing{false};
    std::chrono::steady_clock::time_point m_show_time;
};

#endif // KONKR_POPUPWIDGET_HPP
