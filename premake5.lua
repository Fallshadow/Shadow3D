-- workspace 项目解决方案
workspace "Hazel"
    -- 系统架构，我们这里直接使用 x64
	architecture("x64")
    targetdir "build"
	-- 默认启动项目。其实就是将这个项目在项目设置文件中的位置置顶，以作为启动项目。
	startproject "Sandbox"
    -- 自定义的、应用于生成的 设置集合，是解决方案的必填属性。里面可以填写自己喜欢的名称，其意义取决于它在下面的设置
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
-- 输出目录变量：生成配置（Debug 还是 Release 还是 Dist，即上面的 configurations） - 系统（这里就是 windows） - 系统架构（就是上面的 architecture）
-- 当然这只是一个自定义的输出目录的命名，这里给出的算是很全面了，其实主要还是区分是那个配置输出的，即，根据 configurations 的不同，会生成在不同的文件夹中
local outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- 项目名称
project "Hazel"
    -- 设置生成的工作区或项目文件的目标目录
    -- 这里指解决方案 Hazel 的子项目 Hazel 会在 Hazel 解决方案文件夹的子文件夹 Hazel 下生成
	location "Hazel"
    -- 设置由项目或配置创建的二进制对象的类型，例如控制台或窗口化应用程序，或者共享库或静态库
    -- 这里指共享库 DLL
	kind "SharedLib"
    -- 语言
	language "C++"

    -- 目标输出目录
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    -- 中间输出目录
    -- 中间目录我们使用bin-int而不是obj主要是想跟bin对齐，所以使用int作为后缀的方法。更方便、美观。
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    -- 将指定文件添加到项目中
    -- 这个就是vs的包含和排除文件
	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.c",
        "%{prj.name}/**.hpp", 
		"%{prj.name}/**.cpp" 
	}

    -- 指定附加包含目录
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
	}
    
    -- 系统配置项
	filter "system:windows"
        -- c++语言版本
		cppdialect "C++17"
        -- 系统版本，设置为最新
		systemversion "latest"

        staticruntime "On"
        
        -- 宏定义
		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		-- 调试符号，开启
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		-- 优化代码，发布版本当然要以性能为主
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
    -- 可执行文件
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    dependson 
	{ 
		"Hazel"
    }

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.c",
        "%{prj.name}/**.hpp", 
		"%{prj.name}/**.cpp" 
	}

	includedirs
	{
        "%{prj.name}/src",
        "Hazel/src",
        "Hazel/vendor",
	}

    -- 依赖项链接
	links
	{
		"Hazel"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
        staticruntime "On"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
		}

        postbuildcommands
        {
            ("{COPY} ../bin/" .. outputdir .. "/Hazel/Hazel.dll %{cfg.targetdir}")
        }

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"
    
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"    