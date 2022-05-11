#include "player.h"

Player::Player(const std::string &path) : path_{path}
{
    PlayerErrors err = PlayerErrors::NO_ERROR;
    init(err);
    if (err != PlayerErrors::NO_ERROR)
    {
        std::cerr << "Init Player err, Error: " << err << std::endl;
        throw PlayInitExcept();
    }
}

void Player::init(PlayerErrors &err)
{
    // 计算单帧大小
    unsigned int temp_yuv_frame_len = video_width * video_height * 12 / 8;
    yuv_frame_len = temp_yuv_frame_len;
    if (temp_yuv_frame_len & 0xF)
    {
        yuv_frame_len = (temp_yuv_frame_len & 0xFFF0) + 0x10;
    }

    video_buf = new Uint8[yuv_frame_len];

    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Could not initialize SDL - " << SDL_GetError() << std::endl;
        err = PlayerErrors::SDL_INIT_ERROR;
        return;
    }

    // 创建SDL窗口
    win = SDL_CreateWindow("YUV Player",
                           SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED,
                           w_width,
                           w_height,
                           SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    // 创建窗口出错
    if (!win)
    {
        std::cerr << "Failed to create window, " << SDL_GetError() << std::endl;
        err = PlayerErrors::CREATE_WINDOW_ERROR;
        return;
    }

    // 创建渲染器
    render = SDL_CreateRenderer(win, -1, 0);

    // 为渲染器创建纹理，相当于画布
    texture = SDL_CreateTexture(render,
                                pixformat,
                                SDL_TEXTUREACCESS_STREAMING,
                                video_width,
                                video_height);

    // 创建SDL线程
    pThread = std::make_unique<RefreshThread>();
}

void Player::main_loop(PlayerErrors &err)
{

    // 打开YUV文件
    video_fd = fopen(path_.c_str(), "r");
    if (!video_fd)
    {
        std::cerr << "Failed to open YUV file" << std::endl;
        err = PlayerErrors::OPEN_FILE_ERROR;
        return;
    }
    // 每次读取的数据长度
    unsigned int video_buff_len = 0;

    do
    {
        // 等待事件
        SDL_WaitEvent(&event);

        // 刷新界面事件
        if (event.type == REFRESH_EVENT)
        {
            // 读取块数据
            if ((video_buff_len = fread(video_buf, 1, yuv_frame_len, video_fd)) <= 0)
            {
                std::cout << "播放完毕!" << std::endl;
                break;
            }

            SDL_UpdateTexture(texture, nullptr, video_buf, video_width);
            // 设置拷贝到的窗口大小
            rect.x = 0;
            rect.y = 0;

            SDL_RenderClear(render);
            SDL_RenderCopy(render, texture, nullptr, &rect);
            SDL_RenderPresent(render);
            // 窗口大小改变事件
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            SDL_GetWindowSize(win, &w_width, &w_height);
            rect.w = w_width - 20;
            rect.h = w_height - 20;
        }
        else if (event.type == SDL_QUIT)
        {
            pThread->thread_exit_ = true;
        }
        else if (event.type == QUIT_EVENT)
        {
            break;
        }
    } while (1);
}

Player::~Player()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
    if (render)
    {
        SDL_DestroyRenderer(render);
    }
    if (win)
    {
        SDL_DestroyWindow(win);
    }
    if (video_fd)
    {
        fclose(video_fd);
    }
    if (video_buf != nullptr)
    {
        delete [] video_buf;
    }
    SDL_Quit();
}