namespace DATA
{
    namespace Vars
    {
        extern bool running;
        extern bool isfullscreen;

        namespace Consts
        {
            enum Scenes
            {
                MainMenu,
                Game
            };
            extern int win[2];
        }
    }

    extern int Load();
    extern int Save();
}