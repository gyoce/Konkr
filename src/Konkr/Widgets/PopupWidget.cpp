#include "Konkr/Widgets/PopupWidget.hpp"

PopupWidget::PopupWidget()
{
    m_background_color = { 0, 0, 0, 200 };

    const GuiAnchorLayout::SP main_layout = std::make_shared<GuiAnchorLayout>();
    main_layout->set_stretch({ 0.6f, 1.0f });
    GuiPanel::set_layout(main_layout);

    m_message_label = std::make_shared<GuiText>();
    m_message_label->set_stretch({ 0.7f, 0.7f });
    main_layout->add_widget(m_message_label, Horizontal::Center, Vertical::Center);

    GuiPanel::hide();
}

void PopupWidget::show_popup(const PopupData& data)
{
    m_popup_queue.push(data);
    if (!m_is_showing)
        start_next_popup();
}

void PopupWidget::clear()
{
    m_popup_queue = {};
    hide_current_popup();
}


void PopupWidget::update()
{
    GuiPanel::update();

    if (!m_is_showing)
        return;

    if (m_current_popup.duration_seconds == 0.0f)
        return;

    const auto current_time = std::chrono::steady_clock::now();
    const float elapsed = std::chrono::duration<float>(current_time - m_show_time).count();

    if (elapsed >= m_current_popup.duration_seconds)
    {
        hide_current_popup();
        // Check if there are more popups in queue
        if (!m_popup_queue.empty())
            start_next_popup();
    }
    else if (elapsed >= (m_current_popup.duration_seconds - m_current_popup.fade_duration))
    {
        // Start fading out
        const float fade_progress = (elapsed - (m_current_popup.duration_seconds - m_current_popup.fade_duration)) / m_current_popup.fade_duration;
        apply_fade_effect(fade_progress);
    }
}

void PopupWidget::start_next_popup()
{
    if (m_popup_queue.empty())
        return;

    m_current_popup = m_popup_queue.front();
    m_popup_queue.pop();

    m_message_label->set_text(m_current_popup.message);
    m_message_label->set_text_color(m_current_popup.text_color);
    set_background_color(m_current_popup.background_color);

    GuiPanel::show();
    m_is_showing = true;
    m_show_time = std::chrono::steady_clock::now();
}

void PopupWidget::hide_current_popup()
{
    GuiPanel::hide();
    m_is_showing = false;
}

void PopupWidget::apply_fade_effect(const float fade_progress)
{
    if (!m_is_showing)
      return;

    const float alpha = 1.0f - fade_progress;

    Color bg_color = m_current_popup.background_color;
    bg_color.a = static_cast<uint8_t>(static_cast<float>(m_current_popup.background_color.a) * alpha);
    set_background_color(bg_color);

    Color text_color = m_current_popup.text_color;
    text_color.a = static_cast<uint8_t>(static_cast<float>(m_current_popup.text_color.a) * alpha);
    m_message_label->set_text_color(text_color);
}