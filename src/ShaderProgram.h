#ifndef FRACTALS_SHADERPROGRAM_H
#define FRACTALS_SHADERPROGRAM_H


class ShaderProgram {
public:
    ShaderProgram();

    virtual ~ShaderProgram();

    [[nodiscard]] inline unsigned int getProgramId() const {
        return program_id;
    }

    void useShaderProgram() const;

private:
    unsigned int program_id;
};


#endif //FRACTALS_SHADERPROGRAM_H
