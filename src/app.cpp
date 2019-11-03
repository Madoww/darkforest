#include "app.h"

app::app()
:m_window(sf::VideoMode(1920, 1080, 32), "The Dark Forest dev-build", sf::Style::Fullscreen)
{
    m_window.setVerticalSyncEnabled(true);
    phone.setWindowSize((sf::Vector2f)m_window.getSize());
    scenes = {new GasStation(scene),new Forest(scene),new Shed(scene),new Forest2(scene)};
    cover.setSize(sf::Vector2f(phone.view.getViewport().width*1920,phone.view.getViewport().height*1080));
    cover.setPosition(phone.view.getViewport().left,phone.view.getViewport().top);
    cover.setFillColor(sf::Color::Black);
    background.setTexture(*TextureManager::get("sunset"));
    background.setScale(5,5);
}

app::~app()
{
    if(m_window.isOpen())
    {
        m_window.close();
    }
}

void app::run()
{
    m_status = Status::Running;
    while (m_status != Status::CleaningUp)
    {
		sf::Event windowEvent;
		while (m_window.pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed)
				m_status = Status::CleaningUp;
            if(windowEvent.type == sf::Event::KeyPressed)
            {
                if(windowEvent.key.code == sf::Keyboard::Tab)
                {
                    if(phone.getStatus())
                        phone.setStatus(false);
                    else
                        phone.setStatus(true);
                }
                if(windowEvent.type == sf::Event::KeyPressed)
                {
                    if(windowEvent.key.code == sf::Keyboard::E)
                    {
                        if(inventory.getStatus())
                            inventory.close();
                        else
                            inventory.open();
                    }
                }
            }
            if(windowEvent.type == sf::Event::MouseWheelScrolled)
            {
                if(phone.getPhotosStatus())
                {
                    if(windowEvent.mouseWheelScroll.delta > 0)
                        photos.scroll_down();
                    if(windowEvent.mouseWheelScroll.delta < 0)
                        photos.scroll_up();
                }
                if(phone.getNotesStatus())
                {
                    if(windowEvent.mouseWheelScroll.delta > 0)
                        notes.scroll_down();
                    if(windowEvent.mouseWheelScroll.delta < 0)
                        notes.scroll_up();
                }
            }
		}
        camera.update();
        phone.update();
        /*if(phone.getFlash())
            m_window.setMouseCursorVisible(false);
        else
            m_window.setMouseCursorVisible(true);*/
        m_window.setView(camera.getView());
        Click::instance().update(m_window);
		//m_window.clear(sf::Color(30,30,40));
		m_window.clear(sf::Color(0, 0, 0));//20,20,30  105, 33, 7
		if(scene==0)
		m_window.draw(background);
        /*if(scene==Scene::GasStationScene || scene==Scene::Woods2)
            scenes[1]->draw(m_window);*/
        scenes[scene]->update();
		scenes[scene]->draw(m_window);
        player.draw(m_window);
        Enemies::draw(m_window);
        scenes[scene]->draw_over(m_window);
        //rain.rain(m_window);
        if(scene == Scene::GasStationScene || scene == Scene::Woods)
            leafs.draw(m_window);
            torch.run();
            torch.setScale(player.getPosition());
            torch.draw(m_window,phone.getFlash());
        Enemies::update();
        m_window.setView(camera.getDefaultView());
        Click::instance().update(m_window);
        if(phone.getCameraStatus())
        {
            screenshot.take_screenshot(m_window);
        }
        phone.draw(m_window);
        inventory.draw(m_window);
        dialog.draw(m_window);
        if(phone.getCameraStatus())
        {
            m_window.setView(phone.view);
            m_window.draw(cover);
            scenes[scene]->draw(m_window);
            player.draw(m_window);
            Enemies::draw(m_window);
            scenes[scene]->draw_over(m_window);
            rain.rain(m_window);
            torch.draw(m_window,phone.getFlash());
        }
        //items.update(m_window);
		m_window.display();
	}
}
