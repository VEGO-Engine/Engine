/*!
 * \file Textures.h
 * \brief Forward declaration of the \c Textures enum class.
 *
 * This file contains a forward declaration of the \c Textures enum class, which is used as a base
 * class for texture identifiers in the engine. It allows developers to define their own set of texture
 * types in their own implementation, providing flexibility in texture management within the engine.
 *
 * \details
 * The \c Textures enum class is intended to be implemented by the developer within their own scope.
 * This allows for customized texture entries to be defined based on the specific needs of the project.
 * The base declaration ensures that the enum class can be referenced and used consistently throughout
 * the engine while leaving the details of the texture identifiers up to the implementation.
 */

#pragma once

enum class Textures;