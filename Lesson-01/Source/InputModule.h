// ============================================================================
//
//	Copyright (C) 2013 Josh Vega.
//
//	This file is licensed under the GNU LGPLv3 license. For the license text,
//	please visit: http://opensource.org/licenses/LGPL-3.0.
//
// ============================================================================

#pragma once

class InputModule {
public:
    InputModule(void);

    bool Initialize(void);
    void Shutdown(void);
};